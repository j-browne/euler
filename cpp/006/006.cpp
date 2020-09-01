#include <iostream>
using namespace std;

int main ()
{
	int square_of_sums = 0;
	int sum_of_squares = 0;
	int diff;

	for (int i = 1; i <= 100; i++)
	  {
		square_of_sums += i;
		sum_of_squares += i*i;
	  }

	square_of_sums *= square_of_sums;
	diff = square_of_sums - sum_of_squares;

	cout << diff << endl;
	return 0;
}
