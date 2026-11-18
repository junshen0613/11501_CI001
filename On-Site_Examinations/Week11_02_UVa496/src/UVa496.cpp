#include <iostream>
#include <string>
#include <sstream>
#include <set>
using namespace std;

int main()
{
    string line1, line2;
    while (getline(cin, line1) && getline(cin, line2)) {
        set<int> A, B;
        stringstream ss1(line1), ss2(line2);
        int x;
        while (ss1 >> x) {
            A.insert(x);
        }
        while (ss2 >> x) {
            B.insert(x);
        }
        int common = 0;
        for (int val : A) {
            if (B.count(val)) {
                common++;
            }
        }
        if (common == A.size() && common == B.size()) {
            cout << "A equals B\n";
        }
        else if (common == A.size()) {
            cout << "A is a proper subset of B\n";
        }
        else if (common == B.size()) {
            cout << "B is a proper subset of A\n";
        }
        else if (common == 0) {
            cout << "A and B are disjoint\n";
        }
        else {
            cout << "I'm confused!\n";
        }
    }
    return 0;
}
