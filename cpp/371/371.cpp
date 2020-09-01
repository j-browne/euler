#include <iostream>
#include <iomanip>
using namespace std;

int main ()
{
	double ans = 0;
	int wins = 0;

	for (int x = 0; x < 1000; ++x)
	{
		for (int y = 0; y < 1000; ++y)
		{
			if (x+y==100)
			{
				++wins;
			}
			++ans;
		}
	}

	cout << setprecision(12) << ans/wins << endl;
	return 0;
}
