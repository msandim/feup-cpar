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

void none(long int n, int p)
{
	vector<bool> numbers(n-1, true);
	long int k = 2;

	//#pragma omp parallel num_threads(p)
	while (k*k <= n) {
		

		#pragma omp parallel for num_threads(p)
		// Mark all multiples of k between k*k and n
		for (long int i = k*k; i <= n; i += k) {
			
			if (i%k != 0) {
				i += k - i % k;
			}
			
			
			numbers[i-2] = false;
		}

		#pragma omp master
		// Set k as the smallest urmarked number > k
		for(long int i = k+1; i <= n; i++)
		{
			if (numbers[i-2]) {
				k = i;
				break;
			}
		}
	}

	cout << "Number of primes: " << Utils::countPrimes(numbers) << endl;
	Utils::printPrimes(numbers);
}





void parallel(int improvment, long int n, int p) {
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