#include <iostream>
#include <vector>

using namespace std;

int searchInsert(vector<int> &nums, int target) {
    int i = 0;
    while(i < nums.size() && nums[i] < target) {
        i ++;
    }
    return i;
}

int main() {
    vector<int> nums = {1, 3, 5, 6};

    cout << searchInsert(nums, 5) << endl;
    return 0;
}
