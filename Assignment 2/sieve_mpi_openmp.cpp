#include <iostream>
#include <time.h>
#include <papi.h>
#include <bits/stdc++.h>
#include "mpi.h"
#include "utils.h"

#define BLOCK_LOW(i,n,p) ((i)*(n)/(p))
#define BLOCK_HIGH(i,n,p) (BLOCK_LOW((i)+1,n,p)-1)
#define BLOCK_SIZE(i,n,p) (BLOCK_LOW((i)+1,n,p)-BLOCK_LOW(i,n,p))
#define BLOCK_OWNER(index,n,p) ((((p)*(index)+1)-1)/(n))

using namespace std;


int main(int argc, char* argv[]) {
	
	int rank, size, root = 0;
   
   	MPI_Init( &argc, &argv );
   	MPI_Comm_size( MPI_COMM_WORLD, &size );
   	MPI_Comm_rank( MPI_COMM_WORLD, &rank );

	// Parse input
	if (argc != 3) {
		cerr << "Invalid input: Expected n and p\n";
		return 1;
	}

	// N: Max Number
	long long exponent = atol(argv[1]);
	if (exponent < 1) {
		cerr << "Invalid input: 2^N must equal or superior to 1\n";
		return 1;
	}
	// new_n = 2^n
	long long n = pow(2,exponent);

	// P: Number of threads
	int p = atoi(argv[2]);
	if (p < 0) {
		cerr << "Invalid input: Expected number of processes greater than 0\n";
		return 1;
	}

	// PAPI Setup
	int EventSet = PAPI_NULL;
  	long long values[2];
  	int ret;
  	
	ret = PAPI_library_init( PAPI_VER_CURRENT );
	if ( ret != PAPI_VER_CURRENT )
		cout << "FAIL" << endl;


	ret = PAPI_create_eventset(&EventSet);
	if (ret != PAPI_OK) 
		cout << "ERRO: create eventset" << endl;


	ret = PAPI_add_event(EventSet,PAPI_L1_DCM );
	if (ret != PAPI_OK) 
		cout << "ERRO: PAPI_L1_DCM" << endl;


	ret = PAPI_add_event(EventSet,PAPI_L2_DCM);
	if (ret != PAPI_OK) 
		cout << "ERRO: PAPI_L2_DCM" << endl;


	// PAPI Start
	ret = PAPI_start(EventSet);
	if (ret != PAPI_OK) 
		cout << "ERRO: Start PAPI" << endl;

	struct timespec start, finish;
	double elapsed;
	if (rank == root) {
		clock_gettime(CLOCK_MONOTONIC, &start);
	}

	// Algorithm Execution
	long long block_size = BLOCK_SIZE(rank, n-1, size);
	long long block_low = 2 + BLOCK_LOW(rank, n-1, size);
	long long block_high = 2 + BLOCK_HIGH(rank, n-1, size);

	//vector<bool> numbers(block_size, true);
	bool * numbers = new bool[block_size];
	memset(numbers, true, block_size);

	//int offset = 2;
	long long k = 2;
	long long j;


	// cout << "Rank: " << rank << "  Size: " << BLOCK_SIZE(rank, n, size) << "  Low: " << BLOCK_LOW(rank, n, size) << "  High: " << BLOCK_HIGH(rank, n, size) << endl;
    
	while (k*k <= n) {

		if (k*k < block_low) {
			// Antes
			if (block_low % k == 0)
				j = block_low;
			else  
				j = block_low + (k - (block_low % k));

		} else {
			j = k*k;
		}
		
		// Mark all multiples of k between k*k and n:
		#pragma omp parallel for num_threads(p)
		for (long long i = j; i <= block_high; i += k) {
			numbers[i - block_low] = false;
		}


		// Set k as the smallest urmarked number > k:
		if (rank == root) {

			for(long long i = k + 1; i < block_high; i++) {
				if (numbers[i - block_low]) {
					k = i;
					break;
				}
			}
		}

		MPI_Bcast(&k, 1, MPI_INT, root, MPI_COMM_WORLD);
	}

	int total_primes = 0;
	int block_primes = Utils::countPrimes(numbers, block_size);

	MPI_Reduce(&block_primes, &total_primes, 1, MPI_INT, MPI_SUM, root, MPI_COMM_WORLD);

	if (rank == root) {
		clock_gettime(CLOCK_MONOTONIC, &finish);
		elapsed = (finish.tv_sec - start.tv_sec);
		elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
		cout << "3," << exponent << "," << size << "," << p << "," << total_primes << "," << elapsed << endl; 
		/*
		cout << "N: " << n << endl;
		cout << "Number of primes: " << total_primes << endl;
		cout << "Elapsed time: " << elapsed << endl;
		cout << "************* END OF EXECUTION *************" << endl;
		*/
	}

	delete [] numbers;
	
	// PAPI Stop
	ret = PAPI_stop(EventSet, values);
  		if (ret != PAPI_OK) cout << "ERRO: Stop PAPI" << endl;

	// PAPI Remove
	ret = PAPI_reset( EventSet );
	if ( ret != PAPI_OK )
		cout << "FAIL reset" << endl; 

	ret = PAPI_remove_event( EventSet, PAPI_L1_DCM );
	if ( ret != PAPI_OK )
		cout << "FAIL remove event" << endl; 

	ret = PAPI_remove_event( EventSet, PAPI_L2_DCM );
	if ( ret != PAPI_OK )
		cout << "FAIL remove event" << endl; 

	ret = PAPI_destroy_eventset( &EventSet );
	if ( ret != PAPI_OK )
		cout << "FAIL destroy" << endl;

	
	MPI_Finalize();
}
