traffic-sim: main.o Road.o
	g++ main.o Road.o -o traffic-sim
	rm main.o Road.o

clean:
	rm -f traffic-sim *.o

main.o: main.cpp
	g++ -c main.cpp

Road.o: Road.cpp Road.h macros.h
	g++ -c Road.cpp