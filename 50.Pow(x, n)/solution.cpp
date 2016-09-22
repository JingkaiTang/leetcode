#include <iostream>

using namespace std;

class Solution {
public:
  double myPow(double x, int n) {
    if (n == 0) {
      return 1.0;
    }
    long _n = n;
    bool flag = false;
    if (_n < 0) {
      flag = true;
      _n = -_n;
    }
    double prod = yourPow(x, _n);
    return flag ? 1/prod : prod;
  }
private:
  double yourPow(double x, long n) {
    if (n == 1) {
      return x;
    }

    if (n & 0x1) {
      return x * yourPow(x*x, n>>1);
    } else {
      return yourPow(x*x, n>>1);
    }
  }
};

int main() {
  Solution sln;
  cout << sln.myPow(3, 2) << endl;
  cout << sln.myPow(3, -2) << endl;
  cout << sln.myPow(0.999, 22222222) << endl;
  return 0;
}
