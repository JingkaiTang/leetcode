#include <iostream>
#include <vector>
#include <algorithm>

using namespace std; 

class Solution {
public:
    vector<vector<int>> combinationSum(vector<int> &candidates, int target) {
        if (candidates.size() == 0) {
            return {{}};
        }

        sort(candidates.begin(), candidates.end(), greater<int>());
       
        return combinationSum(candidates.begin(), candidates.end(), target);
    }

    vector<vector<int>> combinationSum(vector<int>::iterator it, vector<int>::iterator end, int target) {
        if (it == end) {
            return {};
        }

        if (*it > target) {
            return combinationSum(++it, end, target);
        }

        if (*it == target) {
            auto result = combinationSum(++it, end, target);
            result.push_back({target});
            return result;
        }

        if (*it < target) {
            auto result = combinationSum(it, end, target-*it);
            for (auto &r: result) {
                r.push_back(*it);
            }
            auto result2 = combinationSum(++it, end, target);
            result.insert(result.end(), result2.begin(), result2.end());
            return result;
        }
        
        return {};
    }
};

int main() {
    vector<int> cdd = {2, 3, 6, 7};
    int target = 7;
    Solution sl;
    auto result = sl.combinationSum(cdd, target);
    for (auto r: result) {
        for (auto i: r) {
            cout << i << " ";
        }
        cout << endl;
    }
}
