#include <iostream>
#include<string>
#include<cctype>

using namespace std;
int main()
{
	string s, t;
	while (getline(cin, s)) {
		getline(cin, t);
		int count1[128] = { 0 }; 
		int count2[128] = { 0 };
		for (char c : s) {
			if (isalpha(c)) {
				count1[tolower(c)]++;
			}
		}
		for (char c : t) {
			if (isalpha(c)) {
				count2[tolower(c)]++;
			}
		}
		for (char ch = 'a'; ch <= 'z'; ch++) {
			int common = min(count1[ch], count2[ch]);
			for (int times = common; times >= 1; times--) {
				cout << ch;
			}
		}
		cout << "\n";
	}
	return 0;
}
