CFLAGS=-std=c++11

all: prog_cpp

prog_cpp:
	g++ $(CFLAGS) -O2 TheSieveOfEratosthenes.cpp -o sieve -l papi -fopenmp
	mpiCC sieve_mpi.cpp -o sieve_mpi -l papi
	mpiCC sieve_mpi_openmp.cpp -o sieve_mpi_openmp -l papi -fopenmp
clean:
	\rm *.o *.class *.csv

test:
	make all
	./sieve 0 3 33554432
	./sieve 1 0 33554432 2
	mpirun -np 8 sieve_mpi 33554432
	#mpirun -np 2 sieve_mpi_openmp 4294967296 400
	
csv:
	make all
	#alinea 1
	for n in 25 26 27 28 29 30 31 32 ; do \
    	#./sieve 0 3 $$n ; \
    	echo $$((2 ** $$n)) ; \
		#echo $$(( 2 ** $$n )) ; \
    done
	#alinea 2
	
	#alinea 3
