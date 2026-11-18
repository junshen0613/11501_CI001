#include <iostream>
#include <string>
#include<map>
#include<sstream>
#include<iomanip>
using namespace std;
int main()
{
    int t;
    if (!(cin >> t))return 0;
    string s;
    getline(cin, s);
    getline(cin, s);
    while (t--) {
        map<string, int>mp;
        int sum = 0;
        while (getline(cin, s)&&s!="") {
            mp[s]++;
            sum++;
        }
        for (const auto& i : mp) {
            cout << i.first << " " << fixed << setprecision(4) << (double)i.second / sum * 100 << "\n";
        }
        if (t)cout << "\n";
    }
    return 0;
}
