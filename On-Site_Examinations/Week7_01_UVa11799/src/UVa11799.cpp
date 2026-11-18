#include <iostream>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;

int main()
{
    int t;
    if (!(cin >> t))return 0;
    for (int casenum = 1; casenum <= t; casenum++) {
        int n;
        cin >> n;
        int maxspeed = 0;
        for (int i = 0; i < n; i++) {
            int speed;
            cin >> speed;
            maxspeed = max(maxspeed, speed);
        }
        cout << "Case " << casenum << ": " << maxspeed << "\n";
    }
    return 0;
}
