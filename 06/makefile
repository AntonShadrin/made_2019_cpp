all: test_BigInt
	
test: test_BigInt
	./test_BigInt
	
test_BigInt: test_BigInt.o BigInt.o
	g++ test_BigInt.o BigInt.o -o test_BigInt

test_BigInt.o:
	g++ -c test.cpp
	
BigInt.o:
	g++ -c BigInt.cpp

clean:
	rm -rf *.o test_BigInt