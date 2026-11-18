#include <iostream>

using namespace std;

int main()
{
    int t;
    cin >> t;
    while (t--) {
        int s;
        cin >> s;
        int result = ((s*567/9+7492)*5-498);
        int tens = abs(result / 10) % 10;
        cout << tens << "\n";
    }
    return 0;
}
