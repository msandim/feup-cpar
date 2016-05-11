all: prog_cpp

prog_cpp:
	g++ -O2 TheSieveOfEratosthenes.cpp -o sieve -l papi -fopenmp

clean:
	\rm *.o *.class *.csv

test:
	make all
	./sieve 0 0 100
	./sieve 0 1 100
	./sieve 0 2 100
	./sieve 1 0 100 4
	
csv:
	make all
	#alinea 1
	./prog_cpp.o 0 0 600 3000 400 0 > output.csv
	java prog_java 0 600 3000 400 0 >> output.csv
	
	#alinea 2
	./prog_cpp.o 1 0 600 3000 400 0 >> output.csv
	java prog_java 1 600 3000 400 0 >> output.csv
	./prog_cpp.o 1 0 4000 10000 2000 0 >> output.csv
	
	#alinea 3
	./prog_cpp.o 0 1 600 3000 400 0 >> output.csv
	./prog_cpp.o 0 2 600 3000 400 0 >> output.csv
	./prog_cpp.o 0 3 600 3000 400 0 >> output.csv
	./prog_cpp.o 0 4 600 3000 400 0 >> output.csv
	./prog_cpp.o 1 1 600 3000 400 0 >> output.csv
	./prog_cpp.o 1 2 600 3000 400 0 >> output.csv
	./prog_cpp.o 1 3 600 3000 400 0 >> output.csv
	./prog_cpp.o 1 4 600 3000 400 0 >> output.csv
