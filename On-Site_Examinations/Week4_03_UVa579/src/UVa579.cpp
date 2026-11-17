#include <iostream>
#include<cmath>
#include<iomanip>
using namespace std;
int main()
{
	int h, m;
	char unit;
	while (cin >> h >> unit >> m) {
		if (h == 0 && m == 0) { break; }
		double hangle = (h % 12) * 30.0 + m * 0.5;
		double mangle = m * 6.0;
		double diff = fabs(hangle - mangle);
		double ans = min(diff, 360.0 - diff);
		cout << fixed << setprecision(3) << ans << "\n";
	}
	return 0;
}
