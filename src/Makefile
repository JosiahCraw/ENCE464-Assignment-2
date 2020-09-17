all: poisson

poisson: poisson_test.c poisson.c
	gcc -O3 -std=c99 -Wall -g3 -o $@ $^

clean:
	rm poisson_test

