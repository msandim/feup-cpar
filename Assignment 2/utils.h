#ifndef UTILS
#define UTILS

using namespace std;

class Utils
{
public:
	static long int countPrimes(const vector<bool> &numbers)
	{
		long int count = 0;

		for(long int i = 0; i < numbers.size(); i++)
		{
			if (numbers[i])
				count++;
		}

		return count;
	}

	static void printPrimes(const vector<bool> &numbers)
	{
		cout << "The primes are: " << endl;

		for(long int i = 0; i < numbers.size(); i++)
		{
			if (numbers[i])
				cout << " " << (i+2) << " ";
		}

		cout << endl;
	}
};

#endif