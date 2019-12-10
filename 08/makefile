all: test
	
test: test_vector
	./test_vector
	
test_vector: test.o
	g++ test.o -o test_vector
	
test.o:
	g++ -c vector.cpp

clean:
	rm -rf *.o test_vector