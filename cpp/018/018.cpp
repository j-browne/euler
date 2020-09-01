#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

void load (ifstream& infile, vector<vector<int> >& vvi)
{
	string str;

	while (infile.good())
	  {
		getline (infile, str);
		vector<int> vi;
		stringstream sstr (str);

		int i;
		while (sstr.good())
		  {
			sstr >> i;
			vi.push_back (i);
		  }

		vvi.push_back (vi);
	  }
	vvi.pop_back();
}

void run (vector<int>& path, int& max, const vector<vector<int> > vvi, int x, int y, int curr)
{
	path.push_back(vvi[y][x]);
	curr += vvi[y][x];
	if (y == vvi.size()-1)
	  {
		if (curr > max)
		  {
			max = curr;

			cout << max << ": ";
			for (vector<int>::iterator it = path.begin(); it != path.end(); ++it)
			  {
				cout << *it << " ";
			  }
			cout << endl;
		  }
	  }
	else
	  {
		run (path, max, vvi, x, y+1, curr);
		run (path, max, vvi, x+1, y+1, curr);
	  }
	path.pop_back();
}

int main ()
{
	ifstream infile ("data");
	vector<vector<int> > vvi;
	load (infile, vvi);
	infile.close();

	vector<int> path;
	int max = 0;

	run (path, max, vvi, 0, 0, 0);

	cout << max << endl;
	return 0;
}
