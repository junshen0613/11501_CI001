#include <iostream>
#include<vector>
using namespace std;
int main()
{
    int n;
    while (cin >> n) {
        vector<int> s(n);
        int count = 0;
        for (int i = 0; i < n; i++) {
            cin >> s[i];
        }
        for (int i = 0; i < n-1; i++) {
            for (int j = i + 1; j < n; j++) {
                if (s[j] < s[i]) {
                    count++;
                }
            }
        }
        cout << "Minimum exchange operations : " << count << "\n";
    }
    return 0;
}
