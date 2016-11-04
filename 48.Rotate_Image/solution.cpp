#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    void rotate(vector<vector<int>> &matrix) {
        int tmp;
        for (int i = 0, j = matrix.size()-1; i < j; i++, j--) {
            for (int k = 0; k < j-i; k++) {
                tmp = matrix[i][i+k];
                matrix[i][i+k] = matrix[j-k][i];
                matrix[j-k][i] = matrix[j][j-k];
                matrix[j][j-k] = matrix[i+k][j];
                matrix[i+k][j] = tmp;
            }
        }
    }
};

void show(vector<vector<int>> &mat) {
    for (auto v: mat) {
        for (auto i: v) {
            cout << i << " ";
        }
        cout << endl;
    }
}

int main() {
    Solution sln;
    vector<vector<int>> mat = {
        {0, 1, 2, 1, 0},
        {2, 4, 5, 4, 3},
        {3, 6, 0, 8, 4},
        {2, 4, 7, 4, 3},
        {0, 5, 6, 5, 0}
    };

    cout << "Origin:" << endl;
    show(mat);
    sln.rotate(mat);
    cout << " Rotated:" << endl;
    show(mat);

    return 0;
}
