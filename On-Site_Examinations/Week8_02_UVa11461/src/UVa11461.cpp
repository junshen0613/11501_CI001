#include <iostream>

using namespace std;
int main()
{
    int a, b;
    while (cin >> a >> b && (a != 0 && b != 0)) {
        int count = 0;
        for (int i = 1; i < 1000; i++) {
            if (i * i >= a) {
                if (i * i <= b) {
                    count++;
                }
            }
        }
        cout << count << "\n";
    }
    return 0;
}
