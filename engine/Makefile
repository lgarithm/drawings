ifeq ($(shell uname), Darwin)
	NPROC = $(shell sysctl -n hw.ncpu)
else
	NPROC = $(shell nproc)
endif

all:
	make -C build

check:
	./tests/run-unit-tests.sh
