#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    string multiply(string num1, string num2) {
        int product = 0;
        for (auto it = num1.cbegin(); it != num1.cend(); ++it) {
            int acc = 0;
            for (auto jt = num2.cbegin(); jt != num2.cend(); ++jt) {
                acc = acc * 10 + (*it-'0') * (*jt-'0');
            }
            product = product * 10 + acc;
        }
        return to_string(product);
    }
};

int main() {
    string n1 = "12345";
    string n2 = "54321";
    Solution sln;
    cout << sln.multiply(n1, n2) << endl;

    return 0;
}
