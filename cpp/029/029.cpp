#include <iostream>
#include <list>
#include "bigint-2009.05.03/BigIntegerLibrary.hh"
using namespace std;

// Exponentiation with a BigInteger result
BigInteger power (int base, int exp)
{
	BigInteger result = 1;
	for (int i = 0; i < exp; ++i)
	  {
		result *= base;
	  }
	return result;
}

int main ()
{
	list<BigInteger> nums;

	// Add every result to a list
	for (int a = 2; a <= 100; ++a)
	  {
		for (int b = 2; b <= 100; ++b)
		  {
			nums.push_back (power (a, b));
		  }
	  }

	// Sort the list and remove the dupes
	nums.sort ();
	nums.unique ();

	// Output the answer
	cout << nums.size () << endl;

	return 0;
}
