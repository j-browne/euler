#include <iostream>
using namespace std;

const int nums[10] = {0, 3, 3, 5, 4, 4, 3, 5, 5, 4};
//const char nums_names[10][10] = {"", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

const int teens[10] = {3, 6, 6, 8, 8, 7, 7, 9, 8, 8};
//const char teens_names[10][10] = {"ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};

const int tens[10] = {0, 0, 6, 6, 5, 5, 5, 7, 6, 6};
//const char tens_names[10][10] = {"", "", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"};

const int exp[4] = {0, 0, 7, 8};
//const char exp_names[10][10] = {"", "", "hundred", "thousand"};

int power (int base, int exp)
{
	long prod = 1;
	for (int i = 0; i < exp; i++)
	  {
		prod *= base;
	  }
	return prod;
}

int length (int n)
{
	int l = 0;
	bool is_and = ((n/100) && (n%100)) ? 1 : 0;

	// exponent
	for (int i = 3; i >= 0; i--)
	  {
		int x = n / power (10, i);
		n = n % power (10, i);

		// for all non-zero digits
		if (x != 0)
		  {
			// if in the tens spot
			if (i == 1)
			  {
				// if in the teens
				if (x == 1)
				  {
					i--;
					x = n / power (10, i);
					n = n % power (10, i);

//					cout << teens_names[x];

					l += teens[x];
				  }
				else
				  {
//					cout << tens_names[x];

					l += tens[x];
				  }
			  }
			else
			  {
//				cout << nums_names[x] << exp_names[i];

				l += (nums[x] + exp[i]);
			  }
		  }
		if (i == 2 && is_and)
		  {
//		  	cout << "and";

			l += 3;
		  }
	  }

//	cout << endl;
	return l;
}

int main ()
{
	int sum = 0;

	for (int i = 1; i <= 1000; i++)
	  {
		sum += length (i);
	  }

	cout << sum << endl;
	return 0;
}
