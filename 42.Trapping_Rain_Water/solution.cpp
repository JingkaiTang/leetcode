#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int trap(vector<int> &height) {
        int water = 0;
        int n = height.size();
        int i = 0;
        while (i < n && height[i] == 0) {
            ++i;
        }
        while (i < n) {
            int j = i;
            int acc = 0;
            int max = -1;
            int max_i = -1;
            int max_acc = 0;
            ++i;
            while (i < n && height[j] > height[i]) {
                if (height[i] >= max) {
                    max = height[i];
                    max_i = i;
                    max_acc = acc;
                }
                acc += height[i];
                ++i;
            }
            if (i < n) {
                water += (i-j-1)*height[j] - acc;
            } else {
                if (max_i > 0) {
                    water += (max_i-j-1)*max - max_acc;
                    i = max_i;
                }
            }
        }

        return water;
    }
};

int main() {
    vector<int> h = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
    Solution sl;
    cout << sl.trap(h) << endl;

    return 0;
}
