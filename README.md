# convo
A little c script that randomly generates a character matrix and applies a constant filter to it horizontally then vertically.

It outputs the combined execution time for the filtering as well as the min/max values of both the output matrices.

### assumptions
When the filter tries to access values in the matrix that are out of bounds, the index it looks at gets set to the nearest in-bound border index.

# usage
```
$ make 
$ ./convo 10 10
computing Dx and Dy execution time: 0.0000069141 seconds 
Dx min: -212, max: 229
Dy min: -236, max: 237
```
