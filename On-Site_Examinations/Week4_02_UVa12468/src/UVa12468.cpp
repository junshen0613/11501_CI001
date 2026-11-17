#include <iostream>
#include<cmath>
#include<algorithm>
using namespace std;
int main()
{
    int a, b;
    while (cin >> a >> b && (a != -1 || b != -1)) {
        int diff = abs(a - b);
        cout << min(diff, 100 - diff) << "\n";
    }
    return 0;
}
