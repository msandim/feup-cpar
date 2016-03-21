//#include <omp.h>
#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <time.h>
#include <cstdlib>
#include <papi.h>

using namespace std;

#define SYSTEMTIME clock_t

 
void OnMult(int m_ar, int debug) 
{
	
	SYSTEMTIME Time1, Time2;
	
	char st[100];
	double temp;
	int i, j, k;

	double *pha, *phb, *phc;
	
	// Initialize matrix:
    pha = (double *)malloc((m_ar * m_ar) * sizeof(double));
	phb = (double *)malloc((m_ar * m_ar) * sizeof(double));
	phc = (double *)malloc((m_ar * m_ar) * sizeof(double));

	for(i=0; i<m_ar; i++)
		for(j=0; j<m_ar; j++)
			pha[i*m_ar + j] = (double)1.0;


	for(i=0; i<m_ar; i++)
		for(j=0; j<m_ar; j++)
			phb[i*m_ar + j] = (double)(i+1);


    Time1 = clock();

    // Do the multiplication:
	for(i=0; i<m_ar; i++)
	{	
		for( j=0; j<m_ar; j++)
		{	
			temp = 0;
			for( k=0; k<m_ar; k++)
			{	
				temp += pha[i*m_ar+k] * phb[k*m_ar+j];
			}
			phc[i*m_ar+j]=temp;
		}
	}

	// Measure the time and give the resulting matrix:
    Time2 = clock();
	printf("C++,Mult,0,%d,%3.3f", m_ar, (double) (Time2 - Time1) / CLOCKS_PER_SEC);

	
	if (debug == 1)
	{
		cout << "Result matrix: " << endl;
		for(j=0; j<min(m_ar*m_ar, 10); j++)
				cout << phc[j] << " ";
		cout << endl;
	}
	
	
    free(pha);
    free(phb);
    free(phc);
}

void OnMultLine(int m_ar, int debug)
{
	SYSTEMTIME Time1, Time2;
	
	char st[100];
	double temp;
	int i, j, k;

	double *pha, *phb, *phc;
	
	// Creates matrix a, b and the result matrix c:
    pha = (double *)malloc((m_ar * m_ar) * sizeof(double));
	phb = (double *)malloc((m_ar * m_ar) * sizeof(double));
	phc = (double *)malloc((m_ar * m_ar) * sizeof(double));

	// Initialize values of matrix a:
	for(i=0; i<m_ar; i++)
		for(j=0; j<m_ar; j++)
			pha[i*m_ar + j] = (double)1.0;

	// Initialize values of matrix b:
	for(i=0; i<m_ar; i++)
		for(j=0; j<m_ar; j++)
			phb[i*m_ar + j] = (double)(i+1);

	// Initialize values of matrix c:
	for(i=0; i<m_ar; i++)
		for(j=0; j<m_ar; j++)
			phc[i*m_ar + j] = (double)0.0;

	// Start the clock:
	Time1 = clock();
    
	for(i=0; i<m_ar; i++)
	{	for( k=0; k<m_ar; k++)
		{	for( j=0; j<m_ar; j++)
			{	
				phc[i*m_ar+j] += pha[i*m_ar+k] * phb[k*m_ar+j];
			}
			
		}
	}

	// Stop the clock:
    Time2 = clock();

	// Show results:
	printf("C++,LineMult,0,%d,%3.3f", m_ar, (double) (Time2 - Time1) / CLOCKS_PER_SEC);

	
	// Print Result matrix (c) - DEBUG:
	if (debug == 1)
	{
		cout << "Result matrix: " << endl;
		for(j=0; j<min(m_ar*m_ar, 10); j++)
				cout << phc[j] << " ";
		cout << endl;
	}
	
	// Unallocate space of the matrices:
	free(pha);
	free(phb);
	free(phc);
}

void OnMultParallel(int m_ar, int n_threads, int debug) 
{
	char st[100];
	double temp;
	int i, j, k;

	double *pha, *phb, *phc;
	
	// Initialize matrix:
    pha = (double *)malloc((m_ar * m_ar) * sizeof(double));
	phb = (double *)malloc((m_ar * m_ar) * sizeof(double));
	phc = (double *)malloc((m_ar * m_ar) * sizeof(double));

	for(i=0; i<m_ar; i++)
		for(j=0; j<m_ar; j++)
			pha[i*m_ar + j] = (double)1.0;


	for(i=0; i<m_ar; i++)
		for(j=0; j<m_ar; j++)
			phb[i*m_ar + j] = (double)(i+1);

	struct timespec start, finish;
	double elapsed;

	clock_gettime(CLOCK_MONOTONIC, &start);

    // Do the multiplication:
	#pragma omp parallel for num_threads(n_threads)
	for(i=0; i<m_ar; i++)
	{	for( j=0; j<m_ar; j++)
		{	temp = 0;
			for( k=0; k<m_ar; k++)
			{	
				temp += pha[i*m_ar+k] * phb[k*m_ar+j];
			}
			phc[i*m_ar+j]=temp;
		}
	}

	// Measure the time and give the resulting matrix:
	clock_gettime(CLOCK_MONOTONIC, &finish);

	elapsed = (finish.tv_sec - start.tv_sec);
	elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
	printf("C++,Mult,%d,%d,%3.3f", n_threads, m_ar, elapsed);

	// Print Result matrix (c) - DEBUG:
	if (debug == 1)
	{
		cout << "Result matrix: " << endl;
		for(j=0; j<min(m_ar*m_ar, 10); j++)
				cout << phc[j] << " ";
		cout << endl;
	}

    free(pha);
    free(phb);
    free(phc);
}

void OnMultLineParallel(int m_ar, int n_threads, int debug)
{
	char st[100];
	double temp;
	int i, j, k;

	double *pha, *phb, *phc;
	
	// Creates matrix a, b and the result matrix c
    pha = (double *)malloc((m_ar * m_ar) * sizeof(double));
	phb = (double *)malloc((m_ar * m_ar) * sizeof(double));
	phc = (double *)malloc((m_ar * m_ar) * sizeof(double));

	//Initialize values of matrix a
	for(i=0; i<m_ar; i++)
		for(j=0; j<m_ar; j++)
			pha[i*m_ar + j] = (double)1.0;

	//Initialize values of matrix b
	for(i=0; i<m_ar; i++)
		for(j=0; j<m_ar; j++)
			phb[i*m_ar + j] = (double)(i+1);

	//Initialize values of matrix c
	for(i=0; i<m_ar; i++)
		for(j=0; j<m_ar; j++)
			phc[i*m_ar + j] = (double)0.0;

	struct timespec start, finish;
	double elapsed;

	clock_gettime(CLOCK_MONOTONIC, &start);
    
	#pragma omp parallel for num_threads(n_threads)
	for(i=0; i<m_ar; i++)
	{	for( k=0; k<m_ar; k++)
		{	for( j=0; j<m_ar; j++)
			{	
				phc[i*m_ar+j] += pha[i*m_ar+k] * phb[k*m_ar+j];
			}
			
		}
	}

	// Measure the time and give the resulting matrix:
	clock_gettime(CLOCK_MONOTONIC, &finish);

	elapsed = (finish.tv_sec - start.tv_sec);
	elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
	printf("C++,LineMult,%d,%d,%3.3f", n_threads, m_ar, elapsed);

	// Print Result matrix (c) - DEBUG:
	if (debug == 1)
	{
		cout << "Result matrix: " << endl;
		for(j=0; j<min(m_ar*m_ar, 10); j++)
				cout << phc[j] << " ";
		cout << endl;
	}

	// Unallocate space of the matrices
	free(pha);
	free(phb);
	free(phc);
}

int main (int argc, char *argv[])
{
	/*
	* op -> 0 - OnMult , 1 - OnMultLine
	* threads -> 0 - seq, 1 - 1 thread, 2 - 2 threads, ...
	*/

	// Parse argv
	if (argc != 7) {
		cout << "Error expected 6 arguments: op threads initial final inc debug(1=on/0=off)";
		return 1;
	}

	int op = atoi(argv[1]);
	int n_threads = atoi(argv[2]);
	int initial = atoi(argv[3]);
	int final = atoi(argv[4]);
	int inc = atoi(argv[5]);
	int debug = atoi(argv[6]);

	char c;
	
	int EventSet = PAPI_NULL;
  	long long values[2];
  	int ret;
	

	ret = PAPI_library_init( PAPI_VER_CURRENT );
	if ( ret != PAPI_VER_CURRENT )
		std::cout << "FAIL" << endl;


	ret = PAPI_create_eventset(&EventSet);
		if (ret != PAPI_OK) cout << "ERRO: create eventset" << endl;


	ret = PAPI_add_event(EventSet,PAPI_L1_DCM );
	if (ret != PAPI_OK) cout << "ERRO: PAPI_L1_DCM" << endl;


	ret = PAPI_add_event(EventSet,PAPI_L2_DCM);
	if (ret != PAPI_OK) cout << "ERRO: PAPI_L2_DCM" << endl;

	int matrixSize = initial;

	do {
		// Start counting:
		ret = PAPI_start(EventSet);
		if (ret != PAPI_OK) cout << "ERRO: Start PAPI" << endl;
		
		switch (op){
			case 0:
				if (n_threads == 0)
					OnMult(matrixSize, debug);
				else 
					OnMultParallel(matrixSize, n_threads, debug);
				break;
			case 1:
				if (n_threads == 0)
					OnMultLine(matrixSize, debug);
				else 
					OnMultLineParallel(matrixSize, n_threads, debug);
				break;
		}
		
		ret = PAPI_stop(EventSet, values);
  		if (ret != PAPI_OK) 
			cout << "ERRO: Stop PAPI" << endl;

		// Print the values of cache faults to csv format:
  		printf(",%lld,%lld\n",values[0], values[1]);
		fflush( stdout );

		ret = PAPI_reset( EventSet );
		if ( ret != PAPI_OK )
			std::cout << "FAIL reset" << endl; 
		
		// Increment the matrix size:
		matrixSize += inc;
	} while (matrixSize <= final);
	
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
