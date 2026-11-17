#include <iostream>
#include<vector> 
#include<string> 
#include<sstream> 
#include<algorithm>
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
    int t;
    cin >> t;
    string line;
    getline(cin, line);
    while (t--) {
        getline(cin, line);
        stringstream ss(line);
        vector<int> nums;
        int x;
        while (ss >> x) {
            nums.push_back(x);
        }
        int max_ans = 1;
        for (int i = 0; i < nums.size(); i++) {
            for (int j = i + 1; j < nums.size(); j++) {
                max_ans = max(max_ans, gcd(nums[i], nums[j]));
            }
        }
        cout << max_ans << "\n";
    }
    return 0;
}
