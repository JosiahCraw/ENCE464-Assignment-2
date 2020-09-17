# ENCE464 Assignment 2

## Optimised Implementation
The optimised implementation can be found in [src/](src/)

## Testing
To perform a correctness test any of the following commands can be used:

```console
user@linux:~$ cd test

# Makes a quick test using 201 size with 10 iterations (This is used by the CI)
user@linux:~$ make all

# Or to do the full test with a size of 901 and 10 iterations use:
user@linux:~$ make looong_test
```

## TODO
    - [ ] Timed testing
    - [ ] Timed testing on remote computer (for consistency)
    - [ ] Optimise out the `if` statements
    - [ ] Add threading
    - [ ] Add GPU Support (Optional)
 
## Authors
Jos Craw <jcr124@uclive.ac.nz>

Ryan Adams <rla97@uclive.ac.nz>