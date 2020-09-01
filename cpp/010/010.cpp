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
	long sum = 0;

	primes.push_back (2);

	for (int i = 3; i < 2000000; i += 2)
	  {
		if (is_prime (i, primes))
		  {
			primes.push_back (i);
			sum += i;
		  }
	  }

	cout << sum << endl;
	return 0;
}
