#include <iostream>
using namespace std;

// Number of days in a month
const int num_days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

// Leap year rule
bool is_leap (int year)
{
	return ((year%4 == 0 && year%100 != 0) || (year%400 == 0));
}

int main ()
{
	int day = 2;
	int sundays = 0;

	// Go through the years
	for (int y = 1901; y < 2001; y++)
	  {
		// Go through the months
		for (int m = 0; m < 12; m++)
		  {
			// If the start of the month is a Sunday, add one to the count
			if (day == 0)
			  {
				sundays++;
			  }
			// Compute the beginning of the next month
			day += num_days[m];
			// Account for a leap year
			if (m == 1 && is_leap (y))
			  {
				day++;
			  }
			day %= 7;
		  }
	  }

	// Output the result
	cout << sundays << endl;
	return 0;
}
