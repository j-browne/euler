#include <iostream>
using namespace std;

int main ()
{
	int tot = 0;

	// Go through each number below 1000
	for (int i = 1; i < 20; i++)
	  {
		// If it's divisible by either 3 or 5, add 1 to tot
		if (i%3 == 0 || i%5 == 0)
		  {
			tot += i;
		  }
	  }

	// output the answer
	cout << tot << endl;
	return 0;
}
