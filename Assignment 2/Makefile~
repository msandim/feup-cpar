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
	./sieve 0 3 32
	./sieve 1 0 25 8
	mpirun -np 8 sieve_mpi 25
	mpirun -np 2 sieve_mpi_openmp 25 4
	
csv:
	make all
	mpirun --hostfile hostfile -np 16 sieve_mpi 32

csv-feup:
	make all
	echo "" > output.csv
	#alinea 1
	#for n in 25 26 27 28 29 30 31 32; do \
	#	./sieve 0 3 $$n >> output.csv; \
	#done; \
	#alinea 2
	#for p in 0 1 2 3 4 5 6 7 8; do \
	#	for n in 25 26 27 28 29 30 31 32; do \
	#		./sieve 1 0 $$n $$p >> output.csv; \
	#	done; \
	#done; \
	#alinea 3 no openmp
	#for p in 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16; do \
	#	for n in 25 26 27 28 29 30 31 32; do \
	#		mpirun --hostfile hostfile -np $$p sieve_mpi $$n >> output.csv; \
	#	done; \
	#done; \
	#alinea 3 with openmp
	for p in 16; do \
		for t in 1 2; do \
			for n in 25 26 27 28 29 30 31 32; do \
				mpirun --hostfile hostfile -np $$p sieve_mpi_openmp $$n $$t >> output.csv; \
			done; \
		done; \
	done; \
