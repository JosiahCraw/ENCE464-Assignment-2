all: quick_test

build: poisson_test.c example/demo_poisson.c ../src/poisson.c
	gcc -O3 -std=c99 -Wall -g3 -o poisson_test $^

build_timed: timed_test.c ../src/poisson.c
	gcc -O3 -std=c99 -Wall -g3 -o timed_test $^

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

timed_test_%: build_timed
	@echo Running Timed Test...
	./scripts/run_timed_test $*
	rm timed_test
	@echo Timed Test Complete!

run_remote_test_%: build_timed
	@echo Running Test Remotely...
	./scripts/remote_test $(host) $(user) $* 10
	@echo Finished Running Remote Test!

clean:
	rm poisson_test
	rm timed_test