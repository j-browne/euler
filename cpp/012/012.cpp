#include <iostream>
#include <fstream>
using namespace std;

int primes[10000];

int power (int base, int exp)
{
	long prod = 1;
	for (int i = 0; i < exp; i++)
	  {
		prod *= base;
	  }
	return prod;
}

int triangle (int n)
{
	return (n * (n+1))/2;
}

int divisors (long n)
{
	int divs = 1;
	// Go through primes less than the current triangle
	for (int j = 0; primes[j] <= n/2 && j < 10000; j++)
	  {
	  	int exp = 0;

		// Add the maximum power of the prime by which n is divisible to divs
		while ((n % power (primes[j], exp)) == 0)
		  {
			exp++;
		  }
		divs *= (exp);
	  }
	return divs;
}

int main ()
{
	// Read in primes
	ifstream infile ("primes");
	for (int i = 0; i < 10000; i++)
	  {
		infile >> primes[i];
	  }
	infile.close ();

	// Go through the triangles
	for (int i = 1; i != 1000000; i++)
	  {
		long t = triangle (i);

		if (divisors (t) >= 500)
		  {
		  	cout << t << endl;
			break;
		  }
	  }

	return 0;
}
