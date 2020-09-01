#include <set>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
using namespace std;

int word_val (const string& s)
{
    int totes = 0;
    for (string::const_iterator it = s.begin (); it < s.end (); ++it)
    {
        totes += (int)(*it);
    }
    return totes;
}

int main ()
{
    set<string> d;
    string s;
    char max[3];
    int maxc = 0;
    int answer;

    ifstream infile ("words-english");
    while (getline (infile, s), infile.good() && !infile.eof())
    {
        d.insert (s);
    }
    infile.close ();

    stringstream ss;
    char key[3] = {'g','o','d'};
    int i = 0;
    infile.open ("cipher1.txt");
    while (getline (infile, s, ','), infile.good() && !infile.eof())
    {
        ss << (char) (atoi (s.c_str()) ^ key[i]);
        i = (i+1)%3;
    }
    infile.close ();
    cout << ss.str() << endl;
    answer = word_val (ss.str ());
/*
    char key[3] = {'a','a','a'};
    for (key[0] = 'a'; key[0] <= 'z'; ++key[0])
    {
        for (key[1] = 'a'; key[1] <= 'z'; ++key[1])
        {
            for (key[2] = 'a'; key[2] <= 'z'; ++key[2])
            {
                int i = 0;
                int c = 0;
                int tot;
                stringstream ss;
                
                infile.open ("cipher1.txt");
                while (getline (infile, s, ','), infile.good() && !infile.eof())
                {
                    ss << (char) (atoi (s.c_str ()) ^ (int) key[i]);
                    i = (i+1)%3;
                }
                infile.close ();

                tot = word_val (ss.str ());

                while (ss >> s, !ss.eof ())
                {
                    if (d.count (s) == 1)
                    {
                        ++c;
                    }
                }


//                cout << key[0] << key[1] << key[2] << endl;
//                cout << ss.str () << endl << endl;
                if (c > maxc)
                {
                    answer = tot;
                    maxc = c;
                    max[0] = key[0];
                    max[1] = key[1];
                    max[2] = key[2];
                }
            }
        }

    }
*/
//    cout << max[0] << max[1] << max[2] << ":" << maxc << endl;
    cout << answer + (int)'.' << endl;
    return 0;
}
