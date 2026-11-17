#include <iostream>

using namespace std;
int gcd(int a, int b) {
    while (b != 0) {
        int temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}
int main()
{
    int x;
    while (cin >> x && x != 0) {
        long long g = 0;
        for (int i = 1; i < x; i++) {
            for (int j = i + 1; j <= x; j++) {
                g += gcd(i, j);
            }
        }
        cout << g << "\n";
    }
    return 0;
}
