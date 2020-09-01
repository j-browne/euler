#include <iostream>
using namespace std;

int main ()
{
	int curr = 1;
	int last = 0;
	int tmp;
	int sum = 0;

	// For each fibonacci number below 4 million
	while (curr < 4000000)
	  {
		// Add it to sum if it is even
		if (curr%2 == 0)
		  {
			sum += curr;
		  }

		// Calculate the next number
		tmp = curr;
		curr += last;
		last = tmp;
	  }

	// Output the answer
	cout << sum << endl;
	return 0;
}
