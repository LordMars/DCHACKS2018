CXXFLAGS  = -Wall -c $(DEBUG) -std=c++11 -pthread

SphinxSrc: SphinxSrc.o
	g++ -std=gnu++11 SphinxSrc.cpp -o SphinxSrc
