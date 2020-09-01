#include <iostream>
#include <valarray>
using namespace std;

void recurs (valarray<int>& v, int depth, int count, int max)
{
	if (depth == 0)
	  {
		++v[count];
		return;
	  }

	for (int i = 1; i <= max; ++i)
	  {
		recurs (v, depth-1, count+i, max);
	  }
}

int main ()
{
	valarray<int> peter (0, 37);
	valarray<int> colin (0, 37);

	recurs (peter, 9, 0, 4);
	recurs (colin, 6, 0, 6);

	double tot = 0;
	for (int i = 1; i <= 36; ++i)
	  {
		tot += (double)peter[i]/peter.sum() - (double)colin[i]/colin.sum();
//		cout << i << '\t' << (double)peter[i]/peter.sum() << '\t' << (double)colin[i]/colin.sum() << endl;
	  }

	cout << peter.sum() << '\t' << colin.sum() << endl;
	cout.precision (7);
	cout << tot << endl;
	return 0;
}
