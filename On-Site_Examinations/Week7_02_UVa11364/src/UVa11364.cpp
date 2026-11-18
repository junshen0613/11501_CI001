#include<iostream>
#include<cmath>
#include<algorithm>
using namespace std;
int main(){
    int t;
    if (!(cin >> t))return 0;
    while (t--){
        int n;
        cin >> n;
        int min_pos = 100;
        int max_pos = -1;
            for (int i = 0; i < n; i++)
            {
                int pos;
                cin >> pos;
                min_pos = min(min_pos, pos);
                max_pos = max(max_pos, pos);
            }
            cout << 2 * (max_pos - min_pos) << "\n";
        }
    }
