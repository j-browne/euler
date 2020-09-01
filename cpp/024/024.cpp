#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

#define MAX 9

void all_rec (string curr, int next, set<int> nums, vector<string>& perms)
{
	nums.erase (next);
	curr += (next + '0');

	if (nums.size() == 0)
	  {
//		cout << curr << endl;
		perms.push_back (curr);
		return;
	  }

	for (set<int>::iterator it = nums.begin (); it != nums.end (); ++it)
	  {
		all_rec (curr, *it, nums, perms);
	  }

	return;
}

void get_perms (set<int> nums, vector<string>& perms)
{
	string curr;

	for (set<int>::iterator it = nums.begin (); it != nums.end (); ++it)
	  {
		all_rec (curr, *it, nums, perms);
	  }

	return;
}

int main ()
{
	vector<string> perms;
	set<int> nums;

	for (int i = 0; i <= MAX; ++i)
	  {
		nums.insert (i);
	  }

	get_perms (nums, perms);

	cout << perms[999999] << endl;

	return 0;
}
