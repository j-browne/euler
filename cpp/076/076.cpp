#include <iostream>
#include <valarray>
using namespace std;

int NUM;

void f (valarray<int>& va, size_t index, int& count)
{
	if (va.sum() > NUM)
	  {
		return;
	  }
	if (va.sum() == NUM)
	  {
		++count;
		return;
	  }
	int max = ((index == -1)?(NUM-1):(va[index]));
	max = ((max > NUM-va.sum())?(NUM-va.sum()):(max));
	for (int i = 1; i <= max; ++i)
	  {
		va[index+1] = i;
		f (va, index+1, count);
	  }
	va[index+1] = 0;
}

int main ()
{
	for (NUM = 2; NUM < 10; ++NUM)
	  {
		valarray<int> va (0, NUM);
		int count = 0;

		f (va, -1, count);

		cout << NUM << ": " << count << endl;
	  }

	return 0;
}
