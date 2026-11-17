#include <iostream>
using namespace std;

int main()
{
    long long n;
    while (cin >> n)
    {
        if (n == 0)
            break;
        while (n >= 10)
        {
            n = (n / 10) + (n % 10);
        }
        cout << n << endl;
    }

    return 0;
}
