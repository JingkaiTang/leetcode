#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int lvp(string s) {
    auto L = '(';
    auto R = ')';
    auto T = '-';

    for (int i = 0; i < s.size();) {
        int count = 0;
        while (i < s.size() && s[i] == R) {
            i ++;
        }

        while (i < s.size()) {
            if (s[i] == L) {
                count ++;
            } else {
                if (count > 0) {
                    count --;
                    s[i] = T;
                    *find(s.rbegin()+s.size()-1-i, s.rend(), L) = T;
                } else {
                    break;
                }
            }
            i ++;
        }
    }

    int longest = 0;
    int len = 0;
    for (auto it = s.begin(); it != s.end();) {
        len = 0;
        while (it != s.end() && *it != T) {
            it ++;
        }
        
        while (it != s.end() && *it == T) {
            it ++;
            len ++;
        }

        longest = max(longest, len);
    }
    
    return longest;
}

int main() {
    string s = "))(()(()(((";

    cout << s << endl << lvp(s) << endl;
    
    return 0;
}

