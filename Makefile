.PHONY: build  test lcov del rebuild
build:
	mkdir build
	cd build && cmake ../
	cd build && make
test:
	cd build/test && ./test_matrix
lcov:
	cd build && 											\
	lcov -t "test/test_matrix" -o Cov.info -c -d . &&		\
	genhtml -o report Cov.info
del:
	rm -rf build
rebuild:
	make del
	make build