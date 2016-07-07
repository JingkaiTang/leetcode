#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int search(vector<int> &nums, int target) {
    int ret = -1;
    for (int i = 0; i < nums.size(); i ++) {
        if (nums[i] == target) {
            ret = i;
            break;
        }
    }

    return ret;
}

int main() {
    vector<int> nums = {4, 5, 6, 7, 0, 1, 2};
    
    for (auto i: nums) {
        cout << i << " ";
    }
    cout << endl;

    cout << 0 << " " << search(nums, 0) << endl;

    return 0;
}
    
