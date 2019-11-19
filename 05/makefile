all: test_serializer
	
test: test_serializer
	./test_serializer
	
test_serializer: test_serializer.o
	g++ test_serializer.o -o test_serializer

test_serializer.o:
	g++ -c main.cpp

clean:
	rm -rf *.o test_serializer