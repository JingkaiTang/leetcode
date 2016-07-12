#include <iostream>
#include <string>
#include <sstream>

using namespace std;

string countAndSay(int n) {
    stringstream ss;
    string str;
    ss << "1";
    for (int i = 1; i < n; i ++) {
        str = ss.str();
        ss.str("");
        for (int j = 0; j < str.size();) {
            char c = str[j];
            int count = 1;
            j ++;
            while (j < str.size() && str[j] == c) {
                count ++;
                j ++;
            }
            ss << count << c;
        }
    }

    return ss.str();
}

int main() {
    cout << countAndSay(8) << endl;

    return 0;
}
