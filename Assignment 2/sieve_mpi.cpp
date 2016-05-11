#include <iostream>
#include <time.h>
#include <papi.h>
#include <bits/stdc++.h>
#include "mpi.h"

#define BLOCK_LOW(i,n,p) ((i)*(n)/(p))
#define BLOCK_HIGH(i,n,p) (BLOCK_LOW((i)+1,n,p)-1)
#define BLOCK_SIZE(i,n,p) (BLOCK_LOW((i)+1,n,p)-BLOCK_LOW(i,n,p))
#define BLOCK_OWNER(index,n,p) ((((p)*(index)+1)-1)/(n))

using namespace std;


int main(int argc, char* argv[]) {
	
	int rank, size;
   
   	MPI_Init( &argc, &argv );
   	MPI_Comm_size( MPI_COMM_WORLD, &size );
   	MPI_Comm_rank( MPI_COMM_WORLD, &rank );

	// Parse input
	if (argc != 2) {
		cerr << "Invalid input: Expected n\n";
		return 1;
	}

	// N: Max Number
	long int n = atol(argv[1]);
	if (n < 2) {
		cerr << "Invalid input: Expected natural number greater than 1\n";
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
	clock_gettime(CLOCK_MONOTONIC, &start);


	cout << size << endl;
	cout << rank << endl;


	// Algorithm Execution
	






	clock_gettime(CLOCK_MONOTONIC, &finish);
	elapsed = (finish.tv_sec - start.tv_sec);
	elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
	cout << "Elapsed time: " << elapsed << endl;

	// PAPI Stop
	ret = PAPI_stop(EventSet, values);
  		if (ret != PAPI_OK) cout << "ERRO: Stop PAPI" << endl;
	
	cout << "N: " << n << endl;
  	cout << "L1 DCM: " << values[0] << endl;
  	cout << "L2 DCM: " << values[1] << endl;

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
	cout << "************* END OF EXECUTION *************" << endl;
}