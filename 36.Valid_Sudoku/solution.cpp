#include <iostream>
#include <vector>
#include <string>

using namespace std;

int bitmap = 0;

void set(int n) {
    bitmap |= 1<<n;
}

bool test(int n) {
    return bitmap & 1<<n;
}

void reset() {
    bitmap = 0;
}

bool isOne2Nine(vector<char> block) {
    reset();
    for (auto c: block) {
        if (c == '.') {
            continue;
        } else {
            int n = c-'0';
            if (test(n)) {
                return false;
            } else {
                set(n);
            }
        }
    }
    return true;
}

bool isValidSudoku(vector<vector<char>> &board) {
    // line
    for (auto block: board) {
        if (!isOne2Nine(block)) {
            return false;
        }
    }

    // column
    for (int i = 0; i < 9; i ++) {
        vector<char> block;
        for (int j = 0; j < 9; j ++) {
            block.push_back(board[j][i]);
        }
        if (!isOne2Nine(block)) {
            return false;
        }
    }

    // block
    for (int i = 0; i < 9; i += 3) {
        for (int j = 0; j < 9; j += 3) {
            vector<char> block; 
            for (int k = i; k < i+3; k ++) {
                for (int l = j; l < j+3; l ++) {
                    block.push_back(board[k][l]);
                }
            }
            if (!isOne2Nine(block)) {
                return false;
            }
        }
    }

    return true;
}

int main() {
    vector<string> data = {
        ".87654321", 
        "2........", 
        "3........", 
        "4........", 
        "5........", 
        "6........", 
        "7........", 
        "8........", 
        "9........"
    };

    vector<vector<char>> board;
    for (auto str: data) {
        vector<char> chars;
        for (auto c: str) {
            chars.push_back(c);
        }
        board.push_back(chars);
    }

    cout << (isValidSudoku(board) ? "Yes" : "No") << endl;

    return 0;
}
