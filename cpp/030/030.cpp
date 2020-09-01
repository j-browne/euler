#include <cmath>
#include <iostream>
using namespace std;

int f (int a)
{
    int s = 0;
    while (a > 0)
      {
        s += pow ((double)(a%10), 5);
        a /= 10;
      }
    return s;
}

int main ()
{
    int s = 0;

    for (int i = 10; i < 999999; ++i)
      {
        if (f (i) == i)
          {
            s += i;
          }
      }

    cout << s << endl;
    return 0;
}
