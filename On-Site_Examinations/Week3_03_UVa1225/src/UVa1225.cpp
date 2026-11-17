#include <iostream>
#include <cstring>
using namespace std;
int digi[10];

int main() {
    int m, n;
    cin >> m;
    while (m--) {
        memset(digi, 0, sizeof(digi));
        cin >> n;
        for (int i = 1; i <= n; i++) {
            int temp = i;
            while (temp > 0) {
                digi[temp % 10]++;
                temp /= 10;
            }
        }
        cout << digi[0];
        for (int j = 1; j <= 9; j++)
            cout << " " << digi[j];
        cout << "\n";
    }
    return 0;
}
