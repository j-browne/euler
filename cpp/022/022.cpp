#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// Compute the "score" of a name, with respect to position.
int score (string str, int pos)
{
	int tot = 0;

	// Go through the word adding up the letters
	for (string::iterator it = str.begin (); it != str.end (); ++it)
	  {
	  	// A=1 ... Z=26
		tot += (int) *it - 'A' + 1;
	  }

	// Multiply by its position in the list.
	tot *= pos;

	return tot;
}

int main ()
{
	long total = 0;
	vector<string> names;

	// Read in the names
	ifstream infile ("names.txt");
	while (!infile.eof ())
	  {
		string tmp;
		infile >> tmp;
		// Leave out the EOF (also, any blank entries?)
		if (tmp.length ())
		  {
			names.push_back (tmp);
		  }
	  }
	infile.close ();

	// Sort the names
	sort (names.begin (), names.end ());

	// Find the score of each name and add it to the total
	int i = 1;
	for (vector<string>::iterator it = names.begin ();
	     it != names.end (); ++it, ++i)
	  {
		total += score (*it, i);
	  }

	// Output the result
	cout << total << endl;
	return 0;
}
