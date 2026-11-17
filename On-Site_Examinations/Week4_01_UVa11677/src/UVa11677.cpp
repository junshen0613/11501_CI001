#include <iostream>
#include<cmath>
#include<algorithm>
using namespace std;
int main()
{
	int h1, m1, h2, m2;
	while (cin >> h1 >> m1 >> h2 >> m2) {
		if (h1 == 0 && m1 == 0 && h2 == 0 && m2 == 0) { break; }
		int start = h1 * 60 + m1;
		int end = h2 * 60 + m2;
		int diff = end - start;
		if (diff < 0) {
			diff += 1440;
		}
		cout << diff << "\n";
	}
	return 0;
}
