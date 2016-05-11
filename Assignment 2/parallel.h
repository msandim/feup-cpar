#ifndef PARALLEL
#define PARALLEL

#ifdef _OPENMP
  #include <omp.h>
  #define TRUE  1
  #define FALSE 0
#else
  #define omp_get_thread_num() 0
  #define omp_get_num_threads() 1
  #define omp_get_nested() 0
#endif

void none(long long n, int p)
{
	//vector<bool> numbers(n-1, true);
	bool * numbers = new bool[n-1];
	memset(numbers, true, n-1);

	long long k = 2;

	//#pragma omp parallel num_threads(p)
	while (k*k <= n) {
		

		#pragma omp parallel for num_threads(p)
		// Mark all multiples of k between k*k and n
		for (long long i = k*k; i <= n; i += k) {
			numbers[i-2] = false;
		}

		//#pragma omp master
		// Set k as the smallest urmarked number > k
		for(long long i = k+1; i <= n; i++)
		{
			if (numbers[i-2] == true) {
				k = i;
				break;
			}
		}
	}

	cout << "Number of primes: " << Utils::countPrimes(numbers, n-1) << endl;
	delete [] numbers;

	//Utils::printPrimes(numbers,  sizeof(numbers));
}





void parallel(int improvment, long long n, int p) {
	struct timespec start, finish;
	double elapsed;
	clock_gettime(CLOCK_MONOTONIC, &start);

	switch (improvment) {
		case 0:
			none(n, p);
			break;
	}

	clock_gettime(CLOCK_MONOTONIC, &finish);
	elapsed = (finish.tv_sec - start.tv_sec);
	elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
	cout << "Elapsed time: " << elapsed << endl;
}

#endif