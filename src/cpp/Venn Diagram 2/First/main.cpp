#include <iostream>
using namespace std;

bool funca(bool p, bool q); //prototypes
bool funcb(bool p, bool q);

int main()
{
    bool p = 0, q = 0;
    cout << "p,     q,  -(p^q),   -pv-q, equivalent?:" << endl;
    for (int i = 0; i <= 1; i++)
    {
        p = i;
        for (int j = 0; j <= 1; j++)
        {
            q = j;
            cout << p << "      " << q << "     " << funca(p,q) << "        " << funcb(p,q) << "    " << (funca(p, q) == funcb(p, q)) << endl;
            //1 is True, 0 is False
        }
    }
    return 0;
}
bool funca(bool p, bool q)
{
    return !(p && q);
}
bool funcb(bool p, bool q)
{
    return !p || !q;
}
