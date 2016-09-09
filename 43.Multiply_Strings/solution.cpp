#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

class Solution {
public:
    string multiply(string num1, string num2) {
        string product = "0";
        for (auto it = num1.cbegin(); it != num1.cend(); ++it) {
            stringstream acc;
            int carry = 0;
            for (auto jt = num2.crbegin(); jt != num2.crend(); ++jt) {
                int tmp = (*it-'0') * (*jt-'0') + carry;
                carry = tmp / 10;
                acc << (tmp % 10);
            }
            if (carry > 0) {
                acc << carry;
            }
            string s_acc = acc.str();
            reverse(s_acc.begin(), s_acc.end());
            if (!equal(product.begin(), product.end(), "0")) {
                product += "0";
            }
            if (find_if(s_acc.begin(), s_acc.end(), [](auto c) {return c != '0';}) != s_acc.end()) {
                product = plus(product, s_acc);
            }
        }
        return product;
    }

    string plus(string num1, string num2) {
        stringstream sum;
        
        int size = num1.size() < num2.size() ? num1.size() : num2.size();
        int carry = 0;
        for (int i = 1; i <= size; ++i) {
            int tmp = (num1[num1.size()-i]-'0') + (num2[num2.size()-i]-'0') + carry;
            carry = tmp / 10;
            sum << (tmp % 10);
        }
        if (num1.size() != num2.size()) {
            string &num = num1.size() > num2.size() ? num1 : num2;
            for (int i = size+1; i <= num.size(); ++i) {
                int tmp = num[num.size()-i]-'0' + carry;
                carry = tmp / 10;
                sum << (tmp % 10);
            }
        }
        if (carry > 0) {
            sum << carry;
        }

        string s_sum = sum.str();
        reverse(s_sum.begin(), s_sum.end());
        return s_sum;
    }
};

int main() {
    string n1 = "0";
    string n2 = "52";
    Solution sln;
    cout << sln.multiply(n1, n2) << endl;

    string m1 = "0";
    string m2 = "0";
    cout << m1 << " + " << m2 << " = " << sln.plus(m1, m2) << endl;
    string p = "0";

    return 0;
}
