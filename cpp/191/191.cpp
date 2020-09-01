#include <vector>
#include <iostream>
using namespace std;

#define ONTIME 0
#define LATE 1
#define ABSENT 2

#define MAX 30

bool valid (const vector<int>& v)
{
	int abs = 0;
	int late = 0;
	for (vector<int>::const_iterator it = v.begin(); it != v.end(); ++it)
	  {
		if (*it == ABSENT)
		  {
			++abs;
		  }
		else
		  {
			abs = 0;
			if (*it == LATE)
			  {
				++late;
			  }
		  }

		if (abs == 3 || late == 2)
		  {
			return false;
		  }
	  }

	return true;
}

void recurs (vector<int>& v, int& count)
{
	int s = v.size();

    if (s == 6)
    {
        for (vector<int>::const_iterator it = v.begin(); it != v.end(); ++it)
        {
            cout << *it;
        }
        cout << endl;
    }

	if (s == MAX)
	  {
		if (valid (v))
		  {
			++count;
		  }
		return;
	  }

	v.push_back (0);
	for (int i = 0; i < 3; ++i)
	  {
		v[s] = i;
		recurs (v, count);
	  }

	v.pop_back();
}

int main ()
{
	int count = 0;
	vector<int> v;

	recurs (v, count);

	cout << count << endl;
	return 0;
}
