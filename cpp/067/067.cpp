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

int main ()
{
	ifstream infile ("data");
	vector<vector<int> > vvi;
	load (infile, vvi);
	infile.close();

	for (size_t i = vvi.size()-1; i != 0; --i)
	  {
		for (size_t j = 1; j < vvi[i].size(); ++j)
		  {
			vvi[i-1][j-1] += ((vvi[i][j-1] > vvi[i][j])?(vvi[i][j-1]):(vvi[i][j]));
		  }
	  }

	cout << vvi[0][0] << endl;
	return 0;
}
