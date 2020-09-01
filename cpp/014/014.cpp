#include <iostream>
using namespace std;

long next (long n)
{
	// even
	if (n%2 == 0)
	  {
		return n/2;
	  }
	// odd
	else
	  {
		return 3*n + 1;
	  }
}

int length (long n)
{
	int l = 1;
	while (n != 1)
	  {
		n = next (n);
		l++;
	  }
	return l;
}

int main ()
{
	int longest_num = 1;
	int longest = 1;

	for (int i = 1; i < 1000000; i++)
	  {
		int l = length (i);
		if (l > longest)
		  {
			longest = l;
			longest_num = i;
		  }
	  }

	cout << longest_num << endl;
	return 0;
}
