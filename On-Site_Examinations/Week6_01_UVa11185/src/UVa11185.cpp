#include <iostream>
#include<string>
#include<algorithm>
using namespace std;
int main()
{
    long long n;
    while (cin >> n && n >= 0) {
        if (n == 0) {
            cout << "0\n";
            continue;
        }
        string ternary = "";
        while (n > 0) {
            ternary += (n%3 + '0');
            n /= 3;
        }
        reverse(ternary.begin(), ternary.end());
        cout << ternary << "\n";
    }
    return 0;
}
