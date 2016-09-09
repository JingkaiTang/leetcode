#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
    bool isMatch(string s, string p) {
        return isMatch(s.begin(), s.end(), p.begin(), p.end());
    }

    bool isMatch(string::iterator sb, string::iterator se, string::iterator pb, string::iterator pe) {
        while (pb != pe) {
            if (*pb == '?') {
                if (sb == se) {
                    return false;
                }
                ++sb;
                ++pb;
            } else if (*pb == '*') {
                ++pb;
                while (pb != pe && *pb == '*') {
                    ++pb;
                }
                if (pb == pe) {
                    return true;
                }
                auto ssb = sb;
                while (ssb != se) {
                    if (isMatch(ssb, se, pb, pe)) {
                        return true;
                    }
                    ++ssb;
                }
                sb = ssb;
            } else {
                if (sb == se || *sb != *pb) {
                    return false;
                }
                ++sb;
                ++pb;
            }
        }

        if (sb != se) {
            return false;
        }

        return true;
    }
};

int main() {
    Solution sln;
    cout << sln.isMatch("aa", "a") << endl;
    cout << sln.isMatch("aa", "aa") << endl;
    cout << sln.isMatch("abefcdgiescdfimde", "ab*cd?i*de") << endl;
    cout << sln.isMatch("aaabbbaabaaaaababaabaaabbabbbbbbbbaabababbabbbaaaaba", "a*******b") << endl;
    cout << sln.isMatch("abbabaaabbabbaababbabbbbbabbbabbbabaaaaababababbbabababaabbababaabbbbbbaaaabababbbaabbbbaabbbbababababbaabbaababaabbbababababbbbaaabbbbbabaaaabbababbbbaababaabbababbbbbababbbabaaaaaaaabbbbbaabaaababaaaabb", "**aa*****ba*a*bb**aa*ab****a*aaaaaa***a*aaaa**bbabb*b*b**aaaaaaaaa*a********ba*bbb***a*ba*bb*bb**a*b*bb") << endl;

    return 0;
}
