#include <iostream>
#include<string>
using namespace std;
char get_mirror(char c) {
    switch (c) {
    case'A':return'A';
    case'E':return'3';
    case'H':return'H';
    case'I':return'I';
    case'J':return'L';
    case'L':return'J';
    case'M':return'M';
    case'O':return'O';
    case'S':return'2';
    case'T':return'T';
    case'U':return'U';
    case'V':return'V';
    case'W':return'W';
    case'X':return'X';
    case'Y':return'Y';
    case'Z':return'5';
    case'1':return'1';
    case'2':return'S';
    case'3':return'E';
    case'5':return'Z';
    case'8':return'8';
    default:return 0;
    }
}
int main()
{
    string s;
    while (cin >> s) {
        bool is_palid = true;
        bool is_mirror = true;
        int left = 0;
        int right = s.length() - 1;
        while (left <= right) {
            if (s[left] != s[right]) {
                is_palid = false;
            }
            char m = get_mirror(s[left]);
            if (m == 0 || m != s[right]) {
                is_mirror = false;
            }
            if (!is_palid && !is_mirror) {
                break;
            }
            left++;
            right--;
        }
        if (!is_palid && !is_mirror) {
            cout << s << " -- is not a palindrome.\n\n";
        }
        else if(!is_palid&&is_mirror){
            cout << s << " -- is a mirrored string.\n\n";
        }
        else if (is_palid && !is_mirror) {
            cout << s << " -- is a regular palindrome.\n\n";
        }
        else {
            cout << s << " -- is a mirrored palindrome.\n\n";
        }
    }
    return 0;
}
