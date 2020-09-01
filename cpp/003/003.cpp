#include <iostream>
using namespace std;

int main ()
{
	long num = 600851475143;
	long largest = 2;

	/* To cut the computational time in about half (I think), we can increment
	   by 2, since there is only one even prime (2), which we can handle
	   separately. */
	// Divide by two as much as possible.
	while (num % 2 == 0)
	  {
		num /= 2;
	  }
	// Divide by each number as much as possible. This will only be possible for
	//  primes, so if it is possible, set that as the largest prime.
	for (long i = 3; num != 1; i += 2)
	  {
		while (num % i == 0)
		  {
			num /= i;
			largest = i;
		  }
	  }

	// Output result
	cout << largest << endl;
	return 0;
}
