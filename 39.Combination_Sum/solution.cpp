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
       
        auto it = candidates.begin();
        while (*it > target) {
           ++it;
        } 
        
        return combinationSum(it, candidates.end(), target);
    }

    vector<vector<int>> combinationSum(vector<int>::iterator it, vector<int>::iterator end, int target) {
        if (it == end) {
            return {{}};
        }

        if (*it == target) {
            return {{target}};
        }
        
        if (*it < target) {
            auto result = combinationSum(++it, end, target-*it);
            for (auto r: result) {
                r.push_back(*it);
            }
            return result;
        }

        return {{}};
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
