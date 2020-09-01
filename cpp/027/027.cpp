#include <set>
#include <iostream>
#include <fstream>
using namespace std;

int main ()
{
    int max = 0;
    int maxa;
    int maxb;

    set<int> primes;
    ifstream infile ("primes.txt");
    while (infile.good() && !infile.eof())
      {
        int n;
        infile >> n;
        primes.insert (n);
      }
    infile.close();

    for (int a = -999; a < 1000; ++a)
      {
        for (int b = -999; b < 1000; ++b)
          {
            for (int n = 0; primes.count (n*n + a*n + b) == 1; ++n)
              {
                if (n > max)
                  {
                    max = n;
                    maxa = a;
                    maxb = b;
                  }
              }
          }
      }

    cout << maxa*maxb << endl;
    return 0;
}
