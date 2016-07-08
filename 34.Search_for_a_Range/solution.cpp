#include <iostream>
#include <vector>

using namespace std;

int searchLeft(vector<int> &nums, int l, int r) {
    int i;
    do {
        i = (l+r)>>1;
        if (nums[r] == nums[i]) {
            r = i;
        } else {
            l = i;
        }
    } while (i != l);
    return nums[l] == nums[r] ? l : r;
}

int searchRight(vector<int> &nums, int r, int l) {
    int i;
    do {
        i = (l+r)>>1;
        if (nums[l] == nums[r]) {
            l = i;
        } else {
            r = i;
        }
    } while (i != l);
    return nums[r] == nums[l] ? r : l;
}

vector<int> searchRange(vector<int> &nums, int target) {
    vector<int> ret;

    if (nums.size() == 0 || target < nums.front() || target > nums.back()) {
        return ret;
    }

    int l = 0;
    int r = nums.size()-1;

    int i;
    
    if (target == nums[0]) {
        i = 0;
        r = searchRight(nums, r, i);
    } else if (target == nums[r]) {
        i = r;
        l = searchLeft(nums, l, i);
    } else {
        do {
            i = (r+l)>>1;
            if (target < nums[i]) {
                r = i;
            } else if (target > nums[i]) {
                l = i;
            } else {
                break;
            }
        } while (i != l && i != r);

        if (target != nums[i]) {
            r = 0;
            l = 1;
        } else {
            l = searchLeft(nums, l, i);
            r = searchRight(nums, r, i);
        }
    }

    for (int j = l; j <= r; j ++) {
        ret.push_back(j);
    }
    return ret;
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
    print(ret);

    return 0;
}

