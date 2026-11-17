#include <iostream>

using namespace std;
void gcd(int a) {
    int g, l;
    cin >> g >> l;
    if (l % g == 0) {
     cout<<-1<<"\n";
    }
    else {
        cout << g << " " << l << "\n";
    }
}
int main()
{
    int t;
    if (cin >> t) {
        while (t--) {
            gcd(t);
        }
    }
    return 0;
}
