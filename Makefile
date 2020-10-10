all: quick_test

build: test/poisson_test.c test/example/demo_poisson.c src/poisson.c
	gcc -Iinclude -O3 -std=gnu99 -Wall -g3 -o poisson_test $^ -lcrypto -lssl -lpthread

build_comp: test/comprehensive_test.c test/example/demo_poisson.c src/poisson.c
	gcc -Iinclude -O3 -std=gnu99 -Wall -g3 -o comp_test $^ -lpthread

build_timed: test/timed_test.c src/poisson.c
	gcc -Iinclude -O3 -std=gnu99 -Wall -g3 -o timed_test $^ -lpthread

quick_test: build
	@echo Running Test...
	./poisson_test 201 50
	rm poisson_test
	@echo Test Passed!

test_comprehensive: build_comp
	@echo Running Test...
	./comp_test 501 100 4
	rm comp_test
	@echo Test Passed!

looong_test: build
	@echo Running Test...
	./poisson_test 901 10
	rm poisson_test
	@echo Test Passed!

timed_test: build_timed
	@echo Running Timed Test...
	test/scripts/run_timed_test $(N) $(iter) $(thread)
	rm timed_test
	@echo Timed Test Complete!

run_remote_test: build_timed
	@echo Running Test Remotely...
	test/scripts/remote_test $(host) $(user) $(N) $(iter)
	@echo Finished Running Remote Test!

clean:
	rm comp_test poisson_test timed_test
