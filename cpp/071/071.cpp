#include <iostream>
#include <queue>
using namespace std;

int gcd (int a, int b)
{
	if (b == 0)
	  {
		return a;
	  }
	else
	  {
		return gcd (b, a%b);
	  }
}

class frac
{
private:
	int num;
	int den;
public:
	frac (int x, int y){num = x; den = y;}
	bool operator< (const frac& other) const {return ((double)num/den < (double)other.num/other.den);}
	bool operator!= (const frac& other) const {return (num != other.num || den != other.den);}
	friend ostream& operator<< (ostream& os, const frac& f);
};

ostream& operator<< (ostream& os, const frac& f)
{
	os << f.num << "/" << f.den;
	return os;
}

int main ()
{
	priority_queue<frac> pq;
	frac f37 (3,7);

	for (int i = 1; i <= 1000000; ++i)
	  {
		int j = 3*i/7;
		while (gcd (i,j) != 1 && j > 0)
		  {
			--j;
		  }
		pq.push (frac(j,i));
	  }

	pq.pop();
	cout << pq.top() << endl;

	return 0;
}
