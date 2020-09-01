#include <iostream>
#include <sstream>
#include <string>
using namespace std;

bool palindrome (int num)
{
	stringstream stream;
	string str;
	string::iterator f;
	string::reverse_iterator b;

	stream << num;
	str = stream.str ();

	for (f = str.begin (), b = str.rbegin ();
	     f != str.end () && b != str.rend ();
	     f++, b++)
	  {
		if (*f != *b)
		  {
			return false;
		  }
	  }

	return true;
}

int main ()
{
	int biggest = 0;

	for (int i = 100; i < 1000; i++)
	  {
		for (int j = i; j < 1000; j++)
		  {
			if (palindrome (i*j) && i*j > biggest)
			  {
				biggest = i*j;
			  }
		  }
	  }

	cout << biggest << endl;
	return 0;
}
