#ifndef UTILS
#define UTILS

using namespace std;

class Utils
{
public:
	static long long countPrimes(const vector<bool> &numbers)
	{
		long long count = 0;

		for(long long i = 0; i < numbers.size(); i++)
		{
			if (numbers[i])
				count++;
		}

		return count;
	}

	static long long countPrimes(const bool * numbers, long long size)
	{
		long long count = 0;

		for(long long i = 0; i < size; i++)
		{
			if (numbers[i])
				count++;
		}

		return count;
	}

	static void printPrimes(const vector<bool> &numbers)
	{
		cout << "The primes are: " << endl;

		for(long long i = 0; i < numbers.size(); i++)
		{
			if (numbers[i])
				cout << " " << (i+2) << " ";
		}

		cout << endl;
	}


	static void printPrimes(const bool * numbers, long long size)
	{
		cout << "The primes are: " << endl;

		for(long long i = 0; i < size; i++)
		{
			if (numbers[i])
				cout << " " << (i+2) << " ";
		}

		cout << endl;
	}

	static long long countPrimesMPI(const vector<bool> &numbers)
	{
		long long count = 0;

		for(long long i = 0; i < numbers.size(); i++)
		{
			if (numbers[i])
				count++;
		}

		return count;
	}

	static long long countPrimesMPI(const bool * numbers, long long size)
	{
		long long count = 0;

		for(long long i = 0; i < size; i++)
		{
			if (numbers[i])
				count++;
		}

		return count;
	}

	static void printPrimesMPI(const vector<bool> &numbers, long long block_low)
	{
		cout << "The primes are: " << endl;

		for(long long i = 0; i < numbers.size(); i++)
		{
			if (numbers[i])
				cout << " " << (block_low + i + 2) << " ";
		}

		cout << endl;
	}

	static void printPrimesMPI(const bool * numbers, long long block_low, long long size)
	{
		cout << "The primes are: " << endl;

		for(long long i = 0; i < size; i++)
		{
			if (numbers[i])
				cout << " " << (block_low + i + 2) << " ";
		}

		cout << endl;
	}


};

#endif