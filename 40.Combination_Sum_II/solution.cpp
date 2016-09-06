#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std; 

class Solution {
public:
    vector<vector<int>> combinationSum2(vector<int> &candidates, int target) {
        if (candidates.size() == 0) {
            return {};
        }

        sort(candidates.begin(), candidates.end(), greater<int>());
       
        return combinationSum2(candidates.begin(), candidates.end(), target, accumulate(candidates.begin(), candidates.end(), 0));
    }

    vector<vector<int>> combinationSum2(vector<int>::iterator it, vector<int>::iterator end, int target, int sum) {
        if (it == end || sum < target) {
            return {};
        }

        int n = *it;

        auto result = combinationSum2(it+1, end, target, sum-n);
        
        if (n == target) {
            bool flag = true;
            for (auto r: result) {
                if (r.size() == 1 && r[0] == n) {
                    flag = false;
                }
            }
            if (flag) {
                result.push_back({n});
            }
        } else if (n < target) {
            auto result2 = combinationSum2(it+1, end, target-n, sum-n);
            for (auto r: result2) {
                bool flag = true;
                for (auto rr: result) {
                    if (rr.back() == n && rr.size() == r.size()+1 && equal(rr.begin(), rr.begin()+r.size(), r.begin())) {
                        flag = false;
                    }
                }

                if (flag) {
                    r.push_back(n);
                    result.push_back(r);
                }
            }
        }

        return result;
    }
};

int main() {
    vector<int> cdd = {10, 1, 2, 7, 6, 1, 5};
    int target = 8;
    Solution sl;
    auto result = sl.combinationSum2(cdd, target);
    for (auto r: result) {
        for (auto i: r) {
            cout << i << " ";
        }
        cout << endl;
    }
}
