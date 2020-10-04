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

# To run a timed test on just the optimised code eg.
user@linux:~$ make timed_test N=2
# This will run tests 1 and 2 so the test

# To run a timed test on just the optimised code on a remote machine:
user@linux:~$ make run_remote_test_201 host=cs19119bs user=jcr124 n=501 iter=20
# This will run the test with a size of 501 and 20 iterations
```

## TODO

- [x] Timed testing
- [x] Timed testing on remote computer (for consistency)
- [x] Optimise out the `if` statements
- [ ] Add threading
- [ ] Add GPU Support (Optional)
 
## Authors
Jos Craw <jcr124@uclive.ac.nz>

Ryan Adams <rla97@uclive.ac.nz>