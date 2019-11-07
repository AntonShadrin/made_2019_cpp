all: testing
	
test: testing
	./testing
	
testing: testing.o parser.o
	g++ testing.o parser.o -o testing

testing.o:
	g++ -c testing.cpp
	
parser.o:
	g++ -c parser.cpp

clean:
	rm -rf *.o testing