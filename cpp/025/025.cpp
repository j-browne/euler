#include <iostream>
#include "bigint-2009.05.03/BigIntegerLibrary.hh"
using namespace std;

int main ()
{
	BigInteger curr = 1;
	BigInteger last = 0;
	BigInteger temp;
	int index = 1;

	// For each fibonacci number with fewer than 100 digits
	while (bigIntegerToString (curr).length () < 1000)
	  {
		// Calculate the next number
		temp = curr;
		curr += last;
		last = temp;

		++index;
	  }

	// Output the answer
	cout << index << endl;

	return 0;
}
