#include <iostream>
#include <vector>
using namespace std;

bool is_prime (int num, vector<int>& primes)
{
	for (vector<int>::iterator i = primes.begin (); i != primes.end (); i++)
	  {
		if (num % *i == 0)
		  {
			return 0;
		  }
	  }

	return 1;
}

int main ()
{
	vector<int> primes;

	for (int i = 2; primes.size () != 10001; i++)
	  {
		if (is_prime (i, primes))
		  {
			primes.push_back (i);
		  }
	  }

	cout << primes.back () << endl;
	return 0;
}
