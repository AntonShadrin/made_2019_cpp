all: calc calc_test
	
run: calc
	./calc ${arg}
	
test: calc_test
	./calc_test

calc: calc.o calculator.o
	g++ calc.o calculator.o -o calc
	
calc_test: calc_test.o calculator.o
	g++ calc_test.o calculator.o -o calc_test

calc.o:
	g++ -c calc.cpp
	
calc_test.o:
	g++ -c calc_test.cpp

calculator.o:
	g++ -c calculator.cpp

clean:
	rm -rf *.o calc calc_test