#include <iostream>
#include <map>
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

int main ()
{
	map<int,int> m;

	for (int i = 1; i < 10000; ++i)
	  {
		m[i] = d(i);
	  }

	int sum = 0;
	for (map<int, int>::iterator it = m.begin(); it != m.end(); ++it)
	  {
		if (it->first != it->second && it->first == m[it->second])
		  {
			sum += it->first;
		  }
	  }
	cout << sum << endl;
	return 0;
}
