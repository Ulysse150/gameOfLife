evolution: evolution.o 
	g++ -std=c++11  console.cpp evolution.hpp evolution.cpp -o launch

all: evolution
	./launch

clean: 
		rm -f *.o executable
		rm -f launch executable


execute:
	./launch
 
