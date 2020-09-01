#include <iostream>
#include <set>
using namespace std;

int d (int a)
{
	int sum = 1;
	for (int i = 2; i*i <= a; ++i)
	  {
		if (a%i == 0)
		  {
			sum += i;
			if (i*i != a)
			  {
				sum += a/i;
			  }
		  }
	  }
	return sum;
}

bool two_abund (int a, const set<int>& abund)
{
	for (set<int>::iterator it = abund.begin(); it != abund.end() && *it < a; ++it)
	  {
		if (abund.count (a-*it) == 1)
		  {
			return true;
		  }
	  }
	return false;
}

int main ()
{
	set<int> abund;

	for (int i = 1; i < 28123; ++i)
	  {
		int div = d(i);
		if (div > i)
		  {
			abund.insert (i);
		  }
	  }

	unsigned long sum = 0;
	for (int i = 1; i < 28123; ++i)
	  {
		if (!two_abund (i, abund))
		  {
			sum += i;
		  }
	  }
	cout << sum << endl;
	return 0;
}
