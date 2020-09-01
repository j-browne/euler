#include <iostream>
using namespace std;

int main ()
{
	int primes[8] = {2, 3, 5, 7, 11, 13, 17, 19};
	int counts[8] = {};
	int smallest = 1;

	for (int i = 2; i <= 20; i++)
	  {
		int n = i;

		for (int j = 0; j < 8; j++)
		  {
			int count = 0;
			while (n%primes[j] == 0)
			  {
				n /= primes[j];
				count++;
			  }

			if (count > counts[j])
			  {
				counts[j] = count;
			  }
		  }
	  }

	for (int i = 0; i < 8; i++)
	  {
		while (counts[i] > 0)
		  {
			smallest *= primes[i];
			counts[i]--;
		  }
	  }

	cout << smallest << endl;
	return 0;
}
