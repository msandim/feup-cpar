CFLAGS=-std=c++11

all: prog_cpp

prog_cpp:
	g++ $(CFLAGS) -O2 TheSieveOfEratosthenes.cpp -o sieve -l papi -fopenmp
	mpiCC sieve_mpi.cpp -o sieve_mpi -l papi
	mpiCC sieve_mpi_openmp.cpp -o sieve_mpi -l papi -fopenmp
clean:
	\rm *.o *.class *.csv

test:
	make all
	#./sieve 0 0 10
	#./sieve 0 1 10
	#./sieve 0 2 10
	./sieve 0 3 4294967296
	#./sieve 1 0 4294967296 8
	#mpirun -np 8 sieve_mpi 4294967296
	#mpirun -np 2 sieve_mpi 4294967296 4
	
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
