all: test_alloc
	
test: test_alloc
	./test_alloc
	
test_alloc: test_alloc.o allocator.o
	g++ test_alloc.o allocator.o -o test_alloc

test_alloc.o:
	g++ -c test_alloc.cpp
	
allocator.o:
	g++ -c allocator.cpp

clean:
	rm -rf *.o test_alloc