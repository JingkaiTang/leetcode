#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  int jump(vector<int> &num) {
    int n = 0;
    int base = 0;
    int bound = 1;

    while (bound < num.size()) {
      int furthest = 0;
      for (int i = base; i < bound; ++i) {
        if (furthest < i+num[i]) {
          furthest = i + num[i];
        }
      }
      ++n;
      base = bound;
      bound = furthest+1;
    }

    return n;
  }
};

int main() {
  vector<int> num = {2, 3, 1, 1, 4};

  Solution sln;
  cout << sln.jump(num) << endl;

  return 0;
}
