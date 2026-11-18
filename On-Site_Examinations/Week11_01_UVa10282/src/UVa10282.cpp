#include <iostream>
#include <string>
#include<map>
#include<sstream>
using namespace std;
int main()
{
    string s,a,b;
    map<string, string>mp;
    while (getline(cin, s)) {
        if (s.empty())break;
        stringstream ss(s);
        ss >> a >> b;
        mp[b] = a;
    }
    while (cin >> b) {
        if (mp.count(b)) {
            cout << mp[b] << "\n";
        }
        else {
            cout << "eh\n";
        }
    }
    return 0;
}
