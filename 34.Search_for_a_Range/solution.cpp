#include <iostream>
#include <vector>

using namespace std;

int searchLeft(vector<int> &nums, int l, int r) {
    int i = (l+r)>>1;
    do {
        if (nums[r] == nums[i]) {
            r = i;
        } else {
            l = i;
        }
        i = (l+r)>>1;
    } while (i != l);
    return nums[l] == nums[r] ? l : r;
}

int searchRight(vector<int> &nums, int l, int r) {
    int i = (l+r)>>1;
    do {
        if (nums[l] == nums[i]) {
            l = i;
        } else {
            r = i;
        }
        i = (l+r)>>1;
    } while (i != l);
    return nums[r] == nums[l] ? r : l;
}

vector<int> searchRange(vector<int> &nums, int target) {
    if (nums.size() == 0 || target < nums.front() || target > nums.back()) {
        return {-1, -1};
    }

    int l = 0;
    int r = nums.size()-1;
    
    if (target == nums[l]) {
        r = searchRight(nums, l, r);
    } else if (target == nums[r]) {
        l = searchLeft(nums, l, r);
    } else {
        int i = (r+l)>>1;
        do {
            if (target < nums[i]) {
                r = i;
            } else if (target > nums[i]) {
                l = i;
            } else {
                break;
            }
            i = (r+l)>>1;
        } while (i != l && i != r);

        if (target != nums[i]) {
            r = -1;
            l = -1;
        } else {
            l = searchLeft(nums, l, i);
            r = searchRight(nums, i, r);
        }
    }

    return {l, r};
}

void print(vector<int> &nums) {
    for (auto i: nums) {
        cout << i << " ";
    }
    cout << endl;
}

int main() {
    vector<int> nums = {5, 7, 7, 8, 8, 10};

    print(nums);

    cout << "find " << 8 << endl;

    auto ret = searchRange(nums, 8);   
    cout << "result:" << endl;
    print(ret);

    return 0;
}

