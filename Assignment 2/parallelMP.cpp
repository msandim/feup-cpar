#include <iostream>
#include <bits/stdc++.h>
#include <time.h>
#include <papi.h>
using namespace std;


// Block Decomposition Macros
#define BLOCK_LOW(i,p,n) (i*n/p)
#define BLOCK_HIGH(i,p,n) (BLOCK_LOW(i+1,p,n)-1)
#define BLOCK_SIZE(i,p,n) (BLOCK_LOW(i+1,p,n)-BLOCK_LOW(i,p,n))
#define BLOCK_OWNER(i,p,n) ((p*i)/n)






void sieveOfEratosthenes(long int n, int p) {
	// Unmarked natural numbers 2, ..., n
	
	//bool arr[] too much storage
	/*
	bool arr[n-1];
	memset(arr, true, sizeof(arr));
	*/

	//vector<bool> less speed
	vector<bool> arr(n-1, true);

	long int k = 2;
	long int smallest = 3;

	struct timespec start, finish;
	double elapsed;

	clock_gettime(CLOCK_MONOTONIC, &start);

	#pragma omp parallel num_threads(p)
	while (k*k <= n) {
		
		#pragma omp for
		// Mark all multiples of k between k*k and n
		for (long int i = k*k; i <= n; i += k) {
			arr[i-2] = false;
		}

		#pragma omp single
		// Set k as the smallest urmarked number > k
		for(long int i = k+1; i <= n; i++)
		{
			if (arr[i-2]) {
				k = i;
				break;
			}
		}
	}

	clock_gettime(CLOCK_MONOTONIC, &finish);

	elapsed = (finish.tv_sec - start.tv_sec);
	elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
	cout << "Elapsed time: " << elapsed << endl;

	// Output
	/*
	cout << "The prime numbers between 1 and " << n << " are:" << endl;
	for (int i = 0; i < n-1; i++) {
		if (arr[i])
			cout << i+2 << "  ";
	}
	cout << endl;
	*/
	
}




int main(int argc, const char* argv[]) {
	
	// Parse input
	if (argc != 3) {
		cerr << "Invalid input: Expected natural number and number of processors\n";
		return 1;
	}

	long int n = atol(argv[1]);
	if (n < 2) {
		cerr << "Invalid input: Expected natural number greater than 1\n";
		return 1;
	}

	int p = atoi(argv[2]);
	if (n < 0) {
		cerr << "Invalid input: Expected number of processors greater than 0\n";
		return 1;
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

	sieveOfEratosthenes(n, p);

	// PAPI Stop
	ret = PAPI_stop(EventSet, values);
  		if (ret != PAPI_OK) cout << "ERRO: Stop PAPI" << endl;
	
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
