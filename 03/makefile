all: testing parse_text

run: parse_text
	./parse_text "${arg}"

test: testing
	./testing
	
parse_text: parse_text.o parser.o
	g++ parse_text.o parser.o -o parse_text

testing: testing.o parser.o
	g++ testing.o parser.o -o testing

parse_text.o:
	g++ -c parse_text.cpp

testing.o:
	g++ -c testing.cpp
	
parser.o:
	g++ -c parser.cpp

clean:
	rm -rf *.o testing parse_text