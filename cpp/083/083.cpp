#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include "Graph.h"
using namespace std;

#define MAX 80

int main ()
{
	Graph<int,int> g;
	vector<int> v;

	int i;
	ifstream infile ("matrix.txt");
	while (infile >> i, infile.good())
	  {
		v.push_back (i);
	  }
	infile.close();

	for (size_t i = 0; i < v.size(); ++i)
	  {
		g.addVertex (i);
        // right & left
		if ((i+1)%MAX != 0)
		  {
			g.addEdge (i, i+1, v[i+1]);
			g.addEdge (i+1, i, v[i]);
		  }
        // down & up
		if ((i+MAX)/MAX < MAX)
		  {
			g.addEdge (i, i+MAX, v[i+MAX]);
			g.addEdge (i+MAX, i, v[i]);
		  }
	  }

	int min = v[0];

	min += g.minimumPaths(0)[MAX*MAX-1];

	cout << min << endl;
	return 0;
}
