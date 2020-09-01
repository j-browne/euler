#include <iostream>
using namespace std;

int main ()
{
	for (int a = 1; a < 334; a++)
	  {
		for (int b = a; b < 667; b++)
		  {
			int c = 1000 - a - b;

			if (c*c == a*a + b*b)
			  {
				cout << a*b*c << endl;
				return 0;
			  }
		  }
	  }
	return 0;
}
