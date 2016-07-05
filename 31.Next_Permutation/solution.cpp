#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

void np(vector<int> &nums) {
    if (nums.size() < 2) {
        return;
    }

    int i = nums.size()-2;
    while (i >= 0 && nums[i] >= nums[i+1]) {
        i --;
    }

    reverse(nums.begin()+i+1, nums.end());
    if (i >= 0) {
        iter_swap(nums.begin()+i, find_if(nums.begin()+i+1, nums.end(), [&nums, &i](int a) { return a > *(nums.begin()+i); }));
    }
}

void print(vector<int> &nums) {
    for (auto n: nums) {
        cout << n << " ";
    }

    cout << endl;
}

int main() {
    vector<int> nums = {3, 2, 1};
    print(nums);
    np(nums);
    print(nums);

    return 0;
}   

