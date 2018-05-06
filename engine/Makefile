ifeq ($(shell uname), Darwin)
	NPROC = $(shell sysctl -n hw.ncpu)
else
	NPROC = $(shell nproc)
endif

BUILD_DIR = build/$(shell uname)

all: build_dir
	make -C $(BUILD_DIR) -j$(NPROC)

build_dir:
	./configure

check:
	./tests/run-unit-tests.sh

profile:
	$(CXX) -std=c++17 -pg -Isrc src/apps/bb8/*.cpp -L$(BUILD_DIR)/lib -lrey -lstdc++fs -pthread
	./a.out -d 4kf -n 6 \
		-l "light((0,0,50), (.1,.1,.1))" \
		-l "light((-20,-20,20), (.7,.7,.7))" \
		-l "light((-20,20,20), (.7,.7,.7))" \
		-l "light((20,-20,20), (.7,.7,.7))" \
		-l "light((20,20,20), (.7,.7,.7))" \
		example_1
	gprof ./a.out > gprof.log
