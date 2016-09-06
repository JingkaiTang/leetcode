#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        int n = nums.size();
        if (n == 0) {
            return 1;
        }
        
        for (int i = 0; i < n;) {
            if (nums[i] > 0 && nums[i] <= n && nums[i] != nums[nums[i]-1]) {
                swap(nums[i], nums[nums[i]-1]);
            } else {
                i ++;
            }
        }

        for (int i = 0; i < n; i ++) {
            if (nums[i] != i+1) {
                return i+1;
            }
        }

        return n+1;
    }
};

int main() {
    vector<int> nums = {-1, 4, 2, 1, 9, 10};

    Solution sl;
    cout << sl.firstMissingPositive(nums) << endl;

    return 0;
}
