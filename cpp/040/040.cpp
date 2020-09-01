#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstdlib>
using namespace std;

#define MAX 6

int main ()
{
    int prod = 1;
    for (int i=1; i <= MAX; ++i)
    {
        int sum = 0;
        for (int j = 1; j <= i; ++j)
        {
            sum += pow (10, j);
        }
        int q = sum/i;
        int r = sum%i;
        char num[MAX+1];
        sprintf (num, "%d", q);
        
        // Just for fun
/*        for (int i = 0; i < r; ++i)
        {
            cout << num[i];
        }
        cout << '[' << (char) num[r] << ']' << num+r+1 << endl;
*/
        num[r+1] = '\0';
        prod *= atoi (num+r);
    }

    cout << prod << endl;
    return 0;
}
