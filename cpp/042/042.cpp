#include <iostream>
#include <cctype>
#include <fstream>
#include <set>
using namespace std;

int triangle (int n)
{
	return n*(n+1)/2;
}

int word_value (const string& s)
{
	int sum = 0;
	for (string::const_iterator it = s.begin(); it != s.end(); ++it)
	  {
		sum += toupper(*it) - 'A' + 1;
	  }
	return sum;
}

int main ()
{
	set<int> triangles;
	int max_index = 1;
	triangles.insert (triangle(1));

	int count = 0;

	string word;
	ifstream infile ("words.txt");
	while (infile.good())
	  {
		infile >> word;
		int val = word_value (word);

		while (val > triangle (max_index))
		  {
		  	++max_index;
			triangles.insert (triangle (max_index));
		  }

		if (triangles.count (val) == 1)
		  {
			++count;
		  }
	  }
	infile.close();

	cout << count << endl;
	return 0;
}
