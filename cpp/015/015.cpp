#include <iostream>
#include <utility>
#include <set>
#include <stack>
#include <vector>
using namespace std;

#define START 0
//#define STOP 5
size_t STOP;

void print_stack (stack<pair<size_t, size_t> > st)
{
	while (st.size() > 0)
	  {
		cout << "(" << st.top().first << "," << st.top().second << ") ";
		st.pop();
	  }
	cout << endl;
}

bool is_valid (pair<size_t, size_t> point)
{
	return (point.first >= START && point.first <= STOP
	        && point.second >= START && point.second <= STOP);
}

void path (set<pair<size_t, size_t> >& se, stack<pair<size_t, size_t> >& st, unsigned long& count)
{
	if (st.size() == 15)
	  {
		print_stack (st);
	  }

	pair<size_t, size_t> curr = st.top();
	if (curr.first == STOP && curr.second == STOP)
	  {
//		print_stack (st);
		++count;
		return;
	  }

	vector<pair<size_t, size_t> > neigh (2, curr);
	
	++(neigh[0].second);
	++(neigh[1].first);

	for (vector<pair<size_t, size_t> >::iterator it = neigh.begin(); it != neigh.end(); ++it)
	  {
		if (is_valid(*it) && se.count(*it) == 0 )
		  {
			st.push(*it);
			se.insert(*it);
			path(se, st, count);
			st.pop();
			se.erase(*it);
		  }
	  }
}

int main ()
{
	cin >> STOP;
	set<pair<size_t, size_t> > se;
	stack<pair<size_t, size_t> > st;
	unsigned long count = 0;

	se.insert (make_pair(START, START));
	st.push (make_pair(START, START));

	path (se, st, count);

	cout << count << endl;

	return 0;
}
