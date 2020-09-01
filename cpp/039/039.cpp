#include <iostream>
#include <cmath>
#include <map>
using namespace std;

#define MAX 1000

int main ()
{
    map<int, int> counts;

    for (int a = 1; a <= MAX-2; ++a)
    {
        for (int b = a; a+b <= MAX-1; ++b)
        {
            for (int c = b; a+b+c <= MAX; ++c)
            {
                if (a*a + b*b == c*c)
                {
                    ++counts[a+b+c];
                }
            }
        }
    }


    int big_p;
    int big_count = 0;
    for (map<int, int>::iterator it = counts.begin(); it != counts.end(); ++it)
    {
        if (it->second > big_count)
        {
            big_count = it->second;
            big_p = it->first;
        }
    }
    cout << big_p << endl;
    return 0;
}
