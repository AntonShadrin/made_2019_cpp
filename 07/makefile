all: test
	
test: test_format
	./test_format
	
test_format: test.o
	g++ test.o -o test_format
	
test.o:
	g++ -c test.cpp

clean:
	rm -rf *.o test_format