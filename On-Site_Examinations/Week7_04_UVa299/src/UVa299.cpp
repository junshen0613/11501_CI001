#include <iostream>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;
void solve() {
    int r;
    cin >> r;
    vector<int> s(r);
    for (int i = 0; i < r; i++) {
        cin >> s[i];
    }
    int count = 0;
    for (int i = 0; i < r; i++) {
        for (int j = i + 1; j < r; j++) {
            if (s[i] > s[j]) {
                count++;
            }
        }
    }
    cout << "Optimal train swapping takes " << count << " swaps.\n";
}
int main()
{
    int n;
    if (cin >> n) {
        while (n--) {
            solve();
        }
    }
    return 0;
}
