#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
  vector<vector<int>> permuteUnique(vector<int> &nums) {
    sort(nums.begin(), nums.end());
    return _(nums);
  }
private:
  vector<vector<int>> _(vector<int> &nums) {
    if (nums.size() == 1) {
      return {nums};
    }
    vector<vector<int>> ret;
    for (auto it = nums.begin(); it != nums.end();) {
      vector<int> vec(nums.size()-1);
      merge(nums.begin(), it, it+1, nums.end(), vec.begin());
      auto rt = _(vec);
      for (auto l: rt) {
        l.push_back(*it);
        ret.push_back(l);
      }
      auto anchor = it;
      ++it;
      while (it != nums.end() && *anchor == *it) {
        ++it;
      }
    }
    return ret;
  }
};

int main() {
  vector<int> nums = {1, 1, 2};

  Solution sln;
  auto ret = sln.permuteUnique(nums);

  for (auto l: ret) {
    for (auto e: l) {
      cout << e << " ";
    }
    cout << endl;
  }
}
