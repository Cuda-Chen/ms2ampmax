#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "libmseed.h"

#include "min_max.h"
#include "standard_deviation.h"

static void
usage ()
{
  printf ("Usage: ./ms2ampmax <mseedfile>\n");
  printf ("\nOutput format: \n");
  printf ("\
<time stamp of the first window contains data>,<station>,<network>,<channel>,<location>,<CR><LF>\n\
<time difference between this window to the first window>,<min>,<max>,<minDemean>,<maxDemean>,<maxamp>,<maxampDemean><CR><LF>\n\
<time difference between this window to the first window>,<min>,<max>,<minDemean>,<maxDemean>,<maxamp>,<maxampDemean><CR><LF>\n\
...  \
\n");
}

int
main (int argc, char **argv)
{
  char *mseedfile      = NULL;
  MS3Record *msr       = NULL;
  uint32_t flags       = 0;
  int8_t verbose       = 0;
  int64_t totalSamples = 0;
  int rv;

  /* Simple argument parsing */
  if (argc != 2)
  {
    usage ();
    return -1;
  }
  mseedfile = argv[1];

  /* Set flags to validate CRCs while reading */
  flags |= MSF_VALIDATECRC;
  /* Unpack the data */
  flags |= MSF_UNPACKDATA;

  /* Get how many number of samples */
  while ((rv = ms3_readmsr (&msr, mseedfile, NULL, NULL,
                            flags, verbose)) == MS_NOERROR)
  {
    totalSamples += msr->samplecnt;
  }

  /* Make sure everything is cleaned up */
  ms3_readmsr (&msr, NULL, NULL, NULL, 0, 0);

  double *data = (double *)malloc (sizeof (double) * totalSamples);
  size_t idx   = 0;
  /* Get the data */
  while ((rv = ms3_readmsr (&msr, mseedfile, NULL, NULL,
                            flags, verbose)) == MS_NOERROR)
  {
    void *sptr;
    size_t i;
    int samplesize;
    char sampletype = msr->sampletype;

    if ((samplesize = ms_samplesize (sampletype)) == 0)
    {
      ms_log (2, "Unrecognized sample type: '%c'\n", msr->sampletype);
    }

    for (i = 0; i < msr->numsamples; i++)
    {
      sptr = (char *)msr->datasamples + (i * samplesize);

      if (sampletype == 'i')
      {
        data[idx] = (double)(*(int32_t *)sptr);
      }
      else if (sampletype == 'f')
      {
        data[idx] = (double)(*(float *)sptr);
      }
      else if (sampletype == 'd')
      {
        data[idx] = (double)(*(double *)sptr);
      }

      idx++;
    }
  }

  /* Make sure everything is cleaned up */
  ms3_readmsr (&msr, NULL, NULL, NULL, 0, 0);

  /* Calculate the min, max, and maxamp with all and demean */
  double mean, SD;
  getMeanAndSD (data, totalSamples, &mean, &SD);
  double min, max, minDemean, maxDemean, maxamp, maxampDemean;
  getMinMaxAndDemean (data, totalSamples, &min, &max,
                      &minDemean, &maxDemean, mean);
  maxamp       = (abs (max) > abs (min)) ? abs (max) : abs (min);
  maxampDemean = (abs (maxDemean) > abs (minDemean)) ? abs (maxDemean) : abs (minDemean);

  printf ("max amplitute of this file: %.2lf,%.2lf\n", maxamp, maxampDemean);

  return 0;
}
