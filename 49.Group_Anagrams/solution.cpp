#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <numeric>

using namespace std;

class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string> &strs) {
        int abcp[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101};
        unordered_map<int, int> sim;
        vector<vector<string>> result;
        for (auto &str: strs) {
            int acc = accumulate(str.begin(), str.end(), 1, [&abcp](int x, char y) {return x * abcp[y-'a'];});
            auto it = sim.find(acc);
            if (it != sim.end()) {
                result[it->second].push_back(str);
            } else {
                sim[acc] = result.size();
                result.push_back({str});
            }
        }
        return result;
    }
};

int main() {
    Solution sln;
    vector<string> strs = {"eat", "tea", "tan", "ate", "nat", "bat"};
    auto ret = sln.groupAnagrams(strs);
    for (auto &group: ret) {
        for (auto &str: group) {
            cout << str << " ";
        }
        cout << endl;
    }

    return 0;
}
