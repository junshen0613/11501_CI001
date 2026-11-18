#include <iostream>
#include <string>
#include<set>
#include<sstream>
#include<cctype>
using namespace std;
int main()
{
    string s;
    set<string>st;
    while (getline(cin, s)) {
        for (int i = 0; i < s.size(); i++) {
            if (isalpha(s[i]))s[i] = tolower(s[i]);
            else s[i] = ' ';
        }
        stringstream ss(s);
        string word;
        while (ss >> word) {
            st.insert(word);
        }
    }
    for (const auto& i : st) {
        cout << i << "\n";
    }
    return 0;
}
