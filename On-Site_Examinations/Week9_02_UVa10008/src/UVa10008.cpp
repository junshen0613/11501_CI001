#include <iostream>
#include<cctype>
#include<string>
using namespace std;

int main()
{
    int n;
    if (!(cin >> n))return 0;
    cin.ignore();
    int count[128] = { 0 };
    string line;
    while (n--) {
        getline(cin, line);
        for (char c: line) {
            if (isalpha(c)) {
                count[toupper(c)]++;
            }
        }
    }
    int max = 0;
    for (char ch = 'A'; ch <= 'Z'; ch++) {
        if (count[ch] > max) {
            max = count[ch];
        }
    }
    for (int times = max; times >= 1; times--) {
        for (char ch = 'A'; ch <= 'Z'; ch++) {
            if (count[ch] == times) {
                cout << ch << " " << times << "\n";
            }
        }
    }
    return 0;
}
