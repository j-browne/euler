#include <iostream>
using namespace std;

#define SUM 200

const int coins[8] = {200,100,50,20,10,5,2,1};
int total = 0;

void rec (int remain, int index = 0)
{
    if (remain == 0)
    {
        ++total;
        return;
    }

    while (coins[index] > remain)
    {
        ++index;
    }

    for (; index < 8; ++index)
    {
        rec (remain - coins[index], index);
    }
}

int main ()
{
    rec (SUM);
    
    cout << total << endl;
    return 0;
}
