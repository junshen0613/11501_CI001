#include <iostream>
#include<string>
using namespace std;

int main()
{
    string s;
    while (cin >> s) {
        if (s[0] == '-')break;
        if (s.size() >= 2 && s[0] == '0' && (s[1] == 'x') || s[1] == 'X') {
            long long val = stoll(s, nullptr, 16);
            cout << val << "\n";
        }
        else {
            long long val = stoll(s);
            cout << "0x";
            cout << uppercase << hex << val << dec << "\n";
        }
    }
    return 0;
}
