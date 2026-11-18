#include <iostream>
#include<string>
#include<algorithm>
using namespace std;
int main()
{
    long long n;
    while (cin >> n && n != 0) {
        string bin = "";
        int cnt = 0;
        while (n > 0) {
            int rem = n % 2;
            bin += (rem + '0');
            if (rem == 1) {
                cnt++;
            }
            n /= 2;
        }
        reverse(bin.begin(), bin.end());
        cout << "The parity of " << bin << " is " << cnt << " (mod 2).\n";
    }
    return 0;
}
