include=-I../../../output/include -I../bb8
libpath=-L../../../output/lib -lrey
cc=g++ -std=c++0x
opts=-O3 -pthread

main:
	$(cc) $(opts) example_main.cpp examples.cpp ../bb8/bb8_model.cpp $(include) $(libpath)
