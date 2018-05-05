ifeq ($(shell uname), Darwin)
	NPROC = $(shell sysctl -n hw.ncpu)
else
	NPROC = $(shell nproc)
endif

all: build
	make -C build

build:
	./configure

check:
	./tests/run-unit-tests.sh
