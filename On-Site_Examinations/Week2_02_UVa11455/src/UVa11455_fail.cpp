#include<iostream>
using namespace std;
int main() {
    int n;
    cin >> n;
    while (n--) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        if (a == d) {
            cout << "square" << "\n";
        }
        else if (a == c && a != b) {
            cout << "rectangle" << "\n";
        }
        else if (a+b>c) {
            cout << "quadrangle" << "\n";
        }
        else {
            cout << "banana" << "\n";
        }
    }
    return 0;
}
