#include <iostream>
#include <bits/stdc++.h>
#include <time.h>
using namespace std;

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

	while (k*k <= n) {
		
		// Mark all multiples of k between k*k and n
		for (long int i = k*k; i <= n; i += k) {
			arr[i-2] = false;
		}

		// Set k as the smallest urmarked number > k
		for(long int i = k+1; i <= n; i++)
		{
			if (arr[i-2]) {
				smallest = i;
				break;
			}
		}
		k = smallest;
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

	sieveOfEratosthenes(n, p);
}