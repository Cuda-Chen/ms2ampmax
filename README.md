# ms2ampmax
Output the maximum amplitude of each miniSEED segment.

# How to Compile and Run
```
$ make
$ ./ms2ampmax <mseedfile path> <time window size> <window overlap>
```
Where `time window size` is second and `window overlap` is percentage.

# Output Format
```
<time stamp of the first window contains data>,<station>,<network>,<channel>,<location>,<CR><LF>
<time difference between this window to the first window>,<min>,<max>,<minDemean>,<maxDemean>,<maxamp>,<maxampDemean><CR><LF>
<time difference between this window to the first window>,<min>,<max>,<minDemean>,<maxDemean>,<maxamp>,<maxampDemean><CR><LF>
... 
```
