#include <iostream>
#include <string>
#include <cstdio>
using namespace std;

bool palindrome (string str)
{
    string::iterator f;
    string::reverse_iterator b;

    for (f = str.begin (), b = str.rbegin ();
         f != str.end () && b != str.rend ();
         f++, b++)
    {
        if (*f != *b)
        {
            return false;
        }
    }

    return true;
}

void binary (int number, string& s)
{
    int remainder;

    if(number <= 1)
    {
        s += (char)(number + '0');
        return;
    }

    remainder = number%2;
    binary(number >> 1, s);
    s += (char)(remainder + '0');
}

int main ()
{
    int sum = 0;

	for (int i = 0; i < 1000000; i++)
    {
        char temp[8];
        sprintf (temp, "%d", i);

        string b10 (temp);
        string b2;

        binary (i, b2);

        if (palindrome (b10) && palindrome (b2))
        {
            sum += i;
        }
    }

    cout << sum << endl;
    return 0;
}
