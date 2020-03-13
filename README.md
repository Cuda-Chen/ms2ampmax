# ms2ampmax
Output the maximum amplitude in each miniSEED input.

# How to Compile and Run
```
$ make
$ ./ms2ampmax <mseedfile path>
```
Where `time window size` is second and `window overlap` is percentage.

# Output Format
```
maximum amplitude of this file: <maximum>,<maximum with demean>
```
