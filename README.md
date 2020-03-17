# ms2ampmax
Output the maximum amplitude in each miniSEED input.

# How to Compile and Run
First clone this repo by typing:
```
$ git clone https://github.com/Cuda-Chen/ms2ampmax.git --recursive
```

Then run:
```
$ make
$ ./ms2ampmax <mseedfile path>
```
Where `time window size` is second and `window overlap` is percentage.

# Output Format
```
maximum amplitude of this file: <maximum>,<maximum with demean>
```

# NOTE
The `mean` value will be rounded to hundredths place.
