#include <iostream>

using namespace std;

bool isPowerOfTwo(int n) {
    if (n <= 0) {
        return false;
    }

    int l = 1;
    while ((n & l) == 0) {
        l <<= 1;
    }
    return n == l;
}

int main() {
    cout << (isPowerOfTwo(2) ? "Yes" : "No") << endl;

    return 0;
}
