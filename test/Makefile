all: poisson_test

poisson_test: poisson_test.c example/demo_poisson.c ../src/poisson.c
	gcc -O3 -std=c99 -Wall -g3 -o demo_example $^
	./demo_example 201 10

clean:
	rm poisson_test