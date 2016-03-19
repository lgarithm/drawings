include=-I../../../build/include -I../bb8 -I../r2d2
libpath=-L../../../build/lib -lrey
cc=g++ -std=c++0x
opts=-O3 -pthread

main:
	$(cc) $(opts) example_main.cpp examples.cpp \
	../bb8/bb8_model.cpp ../r2d2/r2d2_model.cpp \
	$(include) $(libpath)
