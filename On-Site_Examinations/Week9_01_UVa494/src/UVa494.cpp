#include <iostream>
#include<cctype>
#include<string>
using namespace std;

int main()
{
    string line;
    while (getline(cin, line)) {
        int count = 0;
        bool a = false;
        for (int i = 0; i < line.length(); i++) {
            if (isalpha(line[i])) {
                if (!a) {
                    count++;
                    a = true;
                }
            }
            else {
                a = false;
            }
        }
        cout << count << "\n";
    }
    return 0;
}
