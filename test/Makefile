all: quick_test

build: poisson_test.c example/demo_poisson.c ../src/poisson.c
	gcc -O3 -std=c99 -Wall -g3 -o poisson_test $^

quick_test: build
	@echo Running Test...
	./poisson_test 201 10
	rm poisson_test
	@echo Test Passed!

looong_test: build
	@echo Running Test...
	./poisson_test 901 10
	rm poisson_test
	@echo Test Passed!

clean:
	rm poisson_test