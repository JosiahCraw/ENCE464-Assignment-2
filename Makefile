all: quick_test

build: test/poisson_test.c test/example/demo_poisson.c src/poisson.c
	gcc -O3 -std=c99 -Wall -g3 -o poisson_test $^ -lcrypto -lssl

build_comp: test/comprehensive_test.c test/example/demo_poisson.c src/poisson.c
	gcc -O3 -std=c99 -Wall -g3 -o comp_test $^

build_timed: test/timed_test.c src/poisson.c
	gcc -O3 -std=c99 -Wall -g3 -o timed_test $^

quick_test: build
	@echo Running Test...
	./poisson_test 11 5
	rm poisson_test
	@echo Test Passed!

test_comprehensive: build_comp
	@echo Running Test...
	./comp_test 501 100
	rm comp_test
	@echo Test Passed!

looong_test: build
	@echo Running Test...
	./poisson_test 901 10
	rm poisson_test
	@echo Test Passed!

timed_test: build_timed
	@echo Running Timed Test...
	test/scripts/run_timed_test $(N)
	rm timed_test
	@echo Timed Test Complete!

run_remote_test: build_timed
	@echo Running Test Remotely...
	test/scripts/remote_test $(host) $(user) $(N) $(iter)
	@echo Finished Running Remote Test!

clean:
	rm poisson_test timed_test
