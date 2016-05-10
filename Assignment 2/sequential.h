#ifndef SEQUENTIAL
#define SEQUENTIAL

#include <stdio.h>
#include <iostream>
#include "utils.h"
using namespace std;

void use_vector_bit(long int n) {
	vector<bool> numbers(n-1, true);
	long int k = 2;
	long int smallest = 3;

	while (k*k <= n) {
		// Mark all multiples of k between k*k and n:
		for (long int i = k*k; i <= n; i += k)
			numbers[i-2] = false;

		// Set k as the smallest urmarked number > k:
		for(long int i = k+1; i <= n; i++)
		{
			if (numbers[i-2]) {
				smallest = i;
				break;
			}
		}
		k = smallest;
	}

	// Count the number of primes:
	cout << "Number of primes: " << countPrimes(numbers) << endl;
}

void use_unsigned_char(long int n)
{
	unsigned char * numbers;
	numbers = (unsigned char*)malloc((n-1) * sizeof(unsigned char));
	memset(numbers, 1, n-1);
	long int k = 2;
	long int smallest = 3;

	while (k*k <= n) {
		// Mark all multiples of k between k*k and n
		for (long int i = k*k; i <= n; i += k) {
			numbers[i-2] = false;
		}
		// Set k as the smallest urmarked number > k
		for(long int i = k+1; i <= n; i++)
		{
			if (numbers[i-2]) {
				smallest = i;
				break;
			}
		}
		k = smallest;
	}

	// Count the number of primes:
	cout << "Number of primes: " << countPrimes(numbers) << endl;
}

void dont_use_smallest(long int n)
{
	vector<bool> numbers(n-1, true);

	for (long int i = 2; i*i <= n; i++)
	{
		if (numbers[i-2])
		{
			for (long int j = i * i; j <= n-1; j += i)
				numbers[j-2] = 0;
		}
	}

	// Count the number of primes:
	cout << "Number of primes: " << countPrimes(numbers) << endl;
}


void sequential(int improvement, long int n)
{
	struct timespec start, finish;
	double elapsed;
	clock_gettime(CLOCK_MONOTONIC, &start);

	switch (improvement) {
		case 0:
			use_vector_bit(n);
			break;
		case 1:
			use_unsigned_char(n);
			break;
		case 2:
			dont_use_smallest(n);
			break;
	}

	clock_gettime(CLOCK_MONOTONIC, &finish);
	elapsed = (finish.tv_sec - start.tv_sec);
	elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
	cout << "Elapsed time: " << elapsed << endl;
}

#endif