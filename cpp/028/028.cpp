#include <iostream>
using namespace std;

int main ()
{
	int sum = -1;
	int curr = 1;

	for (int i = 1; i <= 1001; ++i)
	  {
		for (int j = 0; j < 2; ++j)
		  {
			if (j == 1 && i%2 == 1)
			  {
				sum += curr - 1;
			  }
			else
			  {
				sum += curr;
			  }

			curr += i;
		  }
	  }

	cout << endl << sum << endl;
	return 0;
}
