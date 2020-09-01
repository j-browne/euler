#include <iostream>
#include <set>
using namespace std;

int pent (int n)
{
	return n*(3*n-1)/2;
}

int main ()
{
	set<int> s;
	unsigned int min = -1;

	for (int i = 1; i < 5000; ++i)
	  {
		s.insert (pent (i));
	  }

	for (set<int>::iterator it = s.begin(); it != s.end(); ++it)
	  {
		for (set<int>::iterator jt = s.begin(); *jt-*it < min && jt != s.end(); ++jt)
		  {
			int sum = *it+*jt;
			int diff = *jt-*it;

			if (diff < min && s.count (sum) == 1 && s.count (diff) == 1)
			  {
				min = diff;
			  }
		  }
	  }

	cout << min << endl;

	return 0;
}
