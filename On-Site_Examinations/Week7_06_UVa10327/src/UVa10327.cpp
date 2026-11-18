#include <iostream>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;

int main()
{
    int r;
    while (cin >> r) {
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
        cout << "Minimum exchange operations : " << count << "\n";
    }
    return 0;
}
