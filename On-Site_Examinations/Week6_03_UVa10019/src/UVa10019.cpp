#include <iostream>
using namespace std;
int sss(int x) {
	int cnt = 0;
	while (x > 0) {
		if (x % 2 == 1)cnt++;
		x /= 2;
	}
	return cnt;
}
int main()
{
	int t;
	if (!(cin >> t))return 0;
	while (t--) {
		int m;
		cin >> m;
		int b1 = sss(m);
		int b2 = 0;
		int temp = m;
		while (temp > 0) {
			int digit = temp % 10;
			b2 += sss(digit);
			temp /= 10;
		}
		cout << b1 << " " << b2 << "\n";
	}
	return 0;
}
