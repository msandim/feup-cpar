#ifndef SEQUENTIAL
#define SEQUENTIAL

#include <stdio.h>
#include <iostream>
#include "utils.h"
using namespace std;

void use_vector_bit(long long n) {
	vector<bool> numbers(n-1, true);
	long long k = 2;
	long long smallest = 3;

	while (k*k <= n) {
		// Mark all multiples of k between k*k and n:
		for (long long i = k*k; i <= n; i += k)
			numbers[i-2] = false;

		// Set k as the smallest urmarked number > k:
		for(long long i = k+1; i <= n; i++)
		{
			if (numbers[i-2]) {
				smallest = i;
				break;
			}
		}
		k = smallest;
	}

	// Plot statistics:
	cout << "Number of primes: " << Utils::countPrimes(numbers) << endl;
	Utils::printPrimes(numbers);
}

void use_bool_array_bit(long long n) {
	bool * numbers = new bool[n-1];
	memset(numbers, true, n-1);

	long long k = 2;
	long long smallest = 3;

	while (k*k <= n) {
		// Mark all multiples of k between k*k and n:
		for (long long i = k*k; i <= n; i += k)
			numbers[i-2] = false;

		// Set k as the smallest urmarked number > k:
		for(long long i = k+1; i <= n; i++)
		{
			if (numbers[i-2]) {
				smallest = i;
				break;
			}
		}
		k = smallest;
	}

	// Plot statistics:
	cout << "Number of primes: " << Utils::countPrimes(numbers, n-1) << endl;
	//Utils::printPrimes(numbers, n-1);
}

void use_unsigned_char(long long n)
{
	unsigned char * numbers;
	numbers = (unsigned char*)malloc((n-1) * sizeof(unsigned char));
	memset(numbers, 1, n-1);
	long long k = 2;
	long long smallest = 3;

	while (k*k <= n) {
		// Mark all multiples of k between k*k and n
		for (long long i = k*k; i <= n; i += k) {
			numbers[i-2] = false;
		}
		// Set k as the smallest urmarked number > k
		for(long long i = k+1; i <= n; i++)
		{
			if (numbers[i-2]) {
				smallest = i;
				break;
			}
		}
		k = smallest;
	}

	// Count the number of primes:
	//cout << "Number of primes: " << Utils::countPrimes(numbers) << endl;
}

void dont_use_smallest(long long n)
{
	vector<bool> numbers(n-1, true);

	for (long long i = 2; i*i <= n; i++)
	{
		if (numbers[i-2])
		{
			for (long long j = i * i; j <= n-1; j += i)
				numbers[j-2] = false;
		}
	}

	// Count the number of primes:
	cout << "Number of primes: " << Utils::countPrimes(numbers) << endl;
	Utils::printPrimes(numbers);
}


void sequential(int improvement, long long n)
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
		case 3:
			use_bool_array_bit(n);
			break;
	}

	clock_gettime(CLOCK_MONOTONIC, &finish);
	elapsed = (finish.tv_sec - start.tv_sec);
	elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
	cout << "Elapsed time: " << elapsed << endl;
}

#endif