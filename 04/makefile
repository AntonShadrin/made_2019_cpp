all: test_matrix
	
test: test_matrix
	./test_matrix
	
test_matrix: test_matrix.o matrix.o
	g++ test_matrix.o matrix.o -o test_matrix

test_matrix.o:
	g++ -c test_matrix.cpp
	
matrix.o:
	g++ -c matrix.cpp

clean:
	rm -rf *.o test_matrix