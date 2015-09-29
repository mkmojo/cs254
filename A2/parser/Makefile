# Trivial makefile for the calculator scanner/parser.
# Depends on default (built-in) rules for C compilation.

# Note that rule for goal (parse) must be the first one in this file.

CXX=g++
CXXFLAGS= -std=c++11 -g 
BIN=parse

parse: parse.o scan.o
	$(CXX)  -o $(BIN) parse.o scan.o 

clean:
	rm -f scan.o parse.o parse

test:
	cat test.txt | ./parse

parse.o: scan.h
scan.o: scan.h
