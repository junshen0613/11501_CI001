#include <iostream>
#include <string>
using namespace std;

int main()
{
    string line;
    while (getline(cin, line)) {
        for (char c : line) {
            if (c != '\r') {
                cout << static_cast<char>(c - 7);
            }
        }
        cout << "\n";
    }
    return 0;
}
