#include<iostream>
using namespace std;
int main() {
    int n;
    int ans;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        if (a > b && a < c && b < c) {
            ans = a;
        }else if (a < b && a > c && b > c) {
            ans = a;
        }
        else if (a > b && a > c && b < c) {
            ans = c;
        }
        else if (a < b && a < c && b > c) {
            ans = c;
        }
        else if (a < b && a < c && b < c) {
            ans = b;
        }
        else if (a > b && a > c && b > c) {
            ans = b;
        }
        cout << "Case " << i << ":" << ans << "\n";
    }
    return 0;
}
