all: test
	
test: test_treads
	./test_treads
	
test_treads: test.o
	g++ test.o -o test_treads
	
test.o:
	g++ -c main.cpp

clean:
	rm -rf *.o test_treads