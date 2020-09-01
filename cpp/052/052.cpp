#include <iostream>
#include <set>
using namespace std;

void get_digs (int i, set<int>& digs)
{
    while (i > 0)
    {
        int n = i%10;
        i /= 10;
        digs.insert (n);
    }
}

bool comp_digs (set<int> digs1, set<int> digs2)
{
    for (set<int>::iterator it = digs1.begin(); it != digs1.end(); ++it)
    {
        if (digs2.count (*it) != 1)
        {
            return false;
        }
    }
    for (set<int>::iterator it = digs2.begin(); it != digs2.end(); ++it)
    {
        if (digs1.count (*it) != 1)
        {
            return false;
        }
    }
    return true;
}

int main ()
{
    for (int i = 100; i < 1000000; ++i)
    {
        set<int> digs;
        get_digs (i, digs);

        for (int j = 2; j < 7; ++j)
        {
            int num = j*i;
            set<int> n_digs;
            get_digs (num, n_digs);

            if (!comp_digs (digs, n_digs))
            {
                break;
            }
            if (j == 6)
            {
                cout << i << endl;
                return 0;
            }
        }
    }

    cout << "NOPE!" << endl;
    return 0;
}
