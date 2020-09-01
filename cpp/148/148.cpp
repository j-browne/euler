#include <iostream>
#include <vector>
using namespace std;

int main()
{
	vector<unsigned long long>* older = new vector<unsigned long long>(1,1);
	int count = 0;

//	while (older->size() < 1000000000)
	while (older->size() < 100)
	  {
	  	cout << "**";
		for (vector<unsigned long long>::iterator it = older->begin(); it != older->end(); ++it)
		  {
			cout << *it << " ";
		  }
		cout << endl;

		vector<unsigned long long>* newer = new vector<unsigned long long>(older->size()+1);
		(*newer)[0] = 1;
		for (size_t i = 1; i < older->size(); ++i)
		  {
			(*newer)[i] = (*older)[i-1] + (*older)[i];
			if ((*newer)[i]%7 != 0)
			  {
				++count;
			  }
		  }
		(*newer)[older->size()] = 1;

		cout << "*" << newer->size() << endl;
		delete older;
		older = newer;
	  }

	delete older;
	cout << count << endl;
	return 0;
}
