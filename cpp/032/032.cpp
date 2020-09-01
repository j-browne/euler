#include <iostream>
#include <set>
using namespace std;

class Digs
{
public:
	int count[10];
	Digs (){clear();};
	Digs (int n){clear();while (n != 0){add(n%10);n/=10;}};
	void clear (){for(int i=0;i<10;++i){count[i]=0;}};
	void add (int j) {++count[j];};
	void print () {for(int i=0;i<10;++i){cout<<i<<'\t'<<count[i]<<endl;}};
	Digs operator+(Digs a){Digs b;for(int i=0;i<10;++i){b.count[i]=a.count[i]+count[i];}return b;};
	bool pandigital (){for(int i=1;i<10;++i){if(count[i]!=1){return false;}}return true;};
	bool repeat (){for(int i=0;i<10;++i){if(count[i]>1){return true;}}return false;};
	int len (){int sum=0;for(int i=0;i<10;++i){sum+=count[i];}return sum;};
};

Digs productDigs (int a, int b)
{
	Digs c(Digs(a)+Digs(b)+Digs(a*b));
	return c;
}

int main ()
{
	set<int> prods;

	for (int i=1;i<10000;++i)
	{
		if (!Digs(i).repeat())
		{
			for (int j=i+1;j<10000;++j)
			{
				if (!Digs(j).repeat())
				{
					Digs prodDigs = productDigs(i,j);
					if (prodDigs.len()>9)
					{
						break;
					}
					if (prodDigs.pandigital())
					{
						//cout << i << '\t' << j << '\t' << i*j << endl;
						prods.insert(i*j);
					}
				}
			}
		}
	}

	int sum = 0;
	for (set<int>::iterator it = prods.begin(); it != prods.end(); ++it)
	{
		sum += *it;
	}
	cout << sum << endl;

	return 0;
}
