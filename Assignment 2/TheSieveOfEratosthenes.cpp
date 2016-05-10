#include <iostream>
#include <time.h>
#include <papi.h>
#include <bits/stdc++.h>

#include "sequential.h"
#include "parallel.h"
#include "mpi.h"
#include "openmp_and_mpi.h"

using namespace std;


int main(int argc, const char* argv[]) {
	
	// Parse input
	if (argc < 4) {
		cerr << "Invalid input: Expected atleast 3 arguments\n";
		return 1;
	}

	// Mode: Sequential = 0, Parallel = 1, MPI = 2, OpenMP + MPI = 3
	int mode = atoi(argv[1]);
	if (mode < 0 || mode > 3) {
		cerr << "Invalid input: Expected mode: Sequential = 0, Parallel = 1, MPI = 2, OpenMP + MPI = 3\n";
		return 1;
	}

	// Improvement: Depends on algorithm
	int improvement = atoi(argv[2]);
	if (improvement < 0) {
		cerr << "Invalid input: Improvement must be euqla or greater than 0\n";
		return 1;
	}

	// N: Max Number
	long int n = atol(argv[3]);
	if (n < 2) {
		cerr << "Invalid input: Expected natural number greater than 1\n";
		return 1;
	}

	int p = 0;
	// If parallelism is activated
	if (mode != 0) {

		if (argc != 5) {
			cerr << "Invalid input: Expected 4 arguments\n";
			return 1;
		}

		// P: Number of Processors
		p = atoi(argv[4]);
		if (n < 0) {
			cerr << "Invalid input: Expected number of processors greater than 0\n";
			return 1;
		}

	}
	

	// PAPI Setup
	int EventSet = PAPI_NULL;
  	long long values[2];
  	int ret;
  	
	ret = PAPI_library_init( PAPI_VER_CURRENT );
	if ( ret != PAPI_VER_CURRENT )
		std::cout << "FAIL" << endl;


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


	// Algorithm Execution
	switch (mode) {
		case 0:
			sequential(improvement, n);
			break;
		case 1:
			parallel(improvement, n, p);
			break;
		case 2:
			mpi(improvement, n, p);
			break;
		case 3:
			openmp_and_mpi(improvement, n, p);
			break;
	}


	// PAPI Stop
	ret = PAPI_stop(EventSet, values);
  		if (ret != PAPI_OK) cout << "ERRO: Stop PAPI" << endl;
	
	printf("Mode: %d\n", mode);
	printf("Improvement: %d\n", improvement);
	printf("N: %li\n", n);
	printf("P: %d\n", p);
  	printf("L1 DCM: %lld \n",values[0]);
  	printf("L2 DCM: %lld \n",values[1]);

	
	// PAPI Remove
	ret = PAPI_reset( EventSet );
	if ( ret != PAPI_OK )
		std::cout << "FAIL reset" << endl; 

	ret = PAPI_remove_event( EventSet, PAPI_L1_DCM );
	if ( ret != PAPI_OK )
		std::cout << "FAIL remove event" << endl; 

	ret = PAPI_remove_event( EventSet, PAPI_L2_DCM );
	if ( ret != PAPI_OK )
		std::cout << "FAIL remove event" << endl; 

	ret = PAPI_destroy_eventset( &EventSet );
	if ( ret != PAPI_OK )
		std::cout << "FAIL destroy" << endl;
}
