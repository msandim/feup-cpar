#ifndef UTILS
#define UTILS

using namespace std;

class Utils
{
public:
	static void countPrimes(const vector<bool> &numbers)
	{
		long int count = 0;

		for(long int i = 0; i < numbers.size(); i++)
			count++;

		return count;
	}
}

#endif