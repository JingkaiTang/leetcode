#include <iostream>
#include <vector>
#include <string>

#define ALL 0b1111111110

using namespace std;

class Bitmap {
public:
    int data;

    Bitmap() : data(0) {
    }

    void set(int n) {
        data |= 1 << n;
    }

    void unset(int n) {
        if (test(n)) {
            data ^= 1 << n;
        }
    }

    bool test(int n) {
        return data & (1 << n);
    }

    void reset() {
        data = 0;
    }

    bool single() {
        return data != 0 && !(data & (data - 1));
    }

    int max() {
        int count = 0;
        while (data >> count != 0) {
            count++;
        }
        return count - 1;
    }
};

void bitmapPrint(Bitmap &bmp) {
    int bound = sizeof(int) << 3;
    for (int i = 0; i < bound; i++) {
        if (bmp.test(i)) {
            cout << i << " ";
        }
    }
    cout << endl;
}

void boardPrint(vector<vector<char>> &board) {
    for (auto chars: board) {
        for (auto c: chars) {
            cout << c << " ";
        }
        cout << endl;
    }
}

bool isOne2Nine(vector<char> block) {
    Bitmap bmp;
    for (auto c: block) {
        if (c == '.') {
            return false;
        } else {
            int n = c - '0';
            if (bmp.test(n)) {
                return false;
            } else {
                bmp.set(n);
            }
        }
    }
    return bmp.data == ALL;
}

bool isSolvedSudoku(vector<vector<char>> &board) {
    // line
    for (auto block: board) {
        if (!isOne2Nine(block)) {
            return false;
        }
    }

    // column
    for (int i = 0; i < 9; i++) {
        vector<char> block;
        for (int j = 0; j < 9; j++) {
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
            for (int k = i; k < i + 3; k++) {
                for (int l = j; l < j + 3; l++) {
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

void blcPrint(string tag, Bitmap blcs[]) {
    cout << tag << "s: ====>" << endl;
    for (int i = 0; i < 9; i++) {
        if (blcs[i].data != 0) {
            cout << "    " << tag << "[" << i << "]" << ": ";
            bitmapPrint(blcs[i]);
        }
    }
    cout << tag << "s <====" << endl;
}

void holdsPrint(Bitmap holds[][9]) {
    cout << "Holds:  ====>" << endl;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (holds[i][j].data != 0) {
                cout << "    Hold[" << i << ", " << j << "]: ";
                bitmapPrint(holds[i][j]);
            }
        }
    }
    cout << "Holds <====" << endl;
}

void solveSudoku(vector<vector<char>> &board) {
    Bitmap blocks[9];
    for (int h = 0, i = 0; i < 9; i += 3) {
        for (int j = 0; j < 9; h++, j += 3) {
            for (int k = i; k < i + 3; k++) {
                for (int l = j; l < j + 3; l++) {
                    if (board[k][l] != '.') {
                        blocks[h].set(board[k][l] - '0');
                    }
                }
            }
        }
    }

    Bitmap lines[9];
    for (int i = 0; i < 9; i++) {
        for (auto c: board[i]) {
            if (c != '.') {
                lines[i].set(c - '0');
            }
        }
    }

    Bitmap columns[9];
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (board[j][i] != '.') {
                columns[i].set(board[j][i] - '0');
            }
        }
    }

    Bitmap holds[9][9];
    int remain = 0;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (board[i][j] == '.') {
                remain++;
                int data = ALL;
                data &= data ^ blocks[i / 3 * 3 + j / 3].data;
                data &= data ^ lines[i].data;
                data &= data ^ columns[j].data;
                holds[i][j].data = data;
            }
        }
    }

    auto blchPrint = [&]() {
        blcPrint("Block", blocks);
        blcPrint("Line", lines);
        blcPrint("Column", columns);
        holdsPrint(holds);
    };

    auto solve = [&](int i, int j, int solved) {
        board[i][j] = '0' + solved;
        blocks[i / 3 * 3 + j / 3].set(solved);
        for (int k = i / 3 * 3; k < i / 3 * 3 + 3; k++) {
            for (int l = j / 3 * 3; l < j / 3 * 3 + 3; l++) {
                holds[k][l].unset(solved);
            }
        }
        lines[i].set(solved);
        for (int k = 0; k < 9; k++) {
            holds[i][k].unset(solved);
        }
        columns[j].set(solved);
        for (int k = 0; k < 9; k++) {
            holds[k][j].unset(solved);
        }
        remain--;
    };

    auto solve_units = [&]() -> bool {
        bool ret = false;
        bool flag = true;
        while (flag) {
            flag = false;
            for (int i = 0; i < 9; i++) {
                for (int j = 0; j < 9; j++) {
                    if (holds[i][j].single()) {
                        solve(i, j, holds[i][j].max());
                        flag = true;
                        ret = true;
                    }
                }
            }
        }
        return ret;
    };

    auto solve_blocks = [&]() -> bool {
        bool ret = false;
        for (int i = 0; i < 9; i++) {
            Bitmap bmp;
            bmp.data = ALL & (ALL ^ blocks[i].data);
            if (bmp.single()) {
                int solved = bmp.max();
                for (int j = i / 3 * 3; j < i / 3 * 3 + 3; j++) {
                    for (int k = i % 3 * 3; k < i % 3 * 3 + 3; k++) {
                        if (holds[j][k].test(solved)) {
                            solve(j, k, solved);
                            ret = true;
                            break;
                        }
                    }
                }
            }
        }
        return ret;
    };

    auto solve_lines = [&]() -> bool {
        bool ret = false;
        for (int i = 0; i < 9; i++) {
            Bitmap bmp;
            bmp.data = ALL & (ALL ^ lines[i].data);
            if (bmp.single()) {
                int solved = bmp.max();
                for (int j = 0; j < 9; j++) {
                    if (holds[i][j].test(solved)) {
                        solve(i, j, solved);
                        ret = true;
                        break;
                    }
                }
            }
        }
        return ret;
    };

    auto solve_columns = [&]() -> bool {
        bool ret = false;
        for (int i = 0; i < 9; i++) {
            Bitmap bmp;
            bmp.data = ALL & (ALL ^ columns[i].data);
            if (bmp.single()) {
                int solved = bmp.max();
                for (int j = 0; j < 9; j++) {
                    if (holds[j][i].test(solved)) {
                        solve(j, i, solved);
                        ret = true;
                        break;
                    }
                }
            }
        }
        return ret;
    };

    auto solve_deep_blocks = [&]() -> bool {
        bool ret = false;
        for (int i = 0; i < 9; i += 3) {
            for (int j = 0; j < 9; j += 3) {
                Bitmap sig;
                Bitmap acc;
                for (int k = i; k < i + 3; k++) {
                    for (int l = j; l < j + 3; l++) {
                        sig.data |= acc.data & holds[k][l].data;
                        acc.data |= holds[k][l].data;
                    }
                }
                sig.data ^= ALL;
                if (sig.data > 0) {
                    for (int k = i; k < i + 3; k++) {
                        for (int l = j; l < j + 3; l++) {
                            int data = holds[k][l].data & sig.data;
                            if (data > 0) {
                                Bitmap bmp;
                                bmp.data = data;
                                if (bmp.single()) {
                                    solve(k, l, bmp.max());
                                    ret = true;
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }
        return ret;
    };

    auto solve_deep_lines = [&]() -> bool {
        bool ret = false;
        for (int i = 0; i < 9; i++) {
            Bitmap sig;
            Bitmap acc;
            for (int j = 0; j < 9; j++) {
                sig.data |= acc.data & holds[i][j].data;
                acc.data |= holds[i][j].data;
            }
            sig.data ^= ALL;
            if (sig.data > 0) {
                for (int j = 0; j < 9; j++) {
                    int data = holds[i][j].data & sig.data;
                    if (data > 0) {
                        Bitmap bmp;
                        bmp.data = data;
                        if (bmp.single()) {
                            solve(i, j, bmp.max());
                            ret = true;
                            break;
                        }
                    }
                }
            }
        }
        return ret;
    };

    auto solve_deep_columns = [&]() -> bool {
        bool ret = false;
        for (int i = 0; i < 9; i++) {
            Bitmap sig;
            Bitmap acc;
            for (int j = 0; j < 9; j++) {
                sig.data |= acc.data & holds[j][i].data;
                acc.data |= holds[j][i].data;
            }
            sig.data ^= ALL;
            if (sig.data > 0) {
                for (int j = 0; j < 9; j++) {
                    int data = holds[j][i].data & sig.data;
                    if (data > 0) {
                        Bitmap bmp;
                        bmp.data = data;
                        if (bmp.single()) {
                            solve(j, i, bmp.max());
                            ret = true;
                            break;
                        }
                    }
                }
            }
        }
        return ret;
    };

    blchPrint();

    bool deep = true;
    while (deep) {
        bool flag = true;
        while (flag) {
            flag = false;
            flag = solve_units() || flag;
            flag = solve_blocks() || flag;
            flag = solve_lines() || flag;
            flag = solve_columns() || flag;
        }

        deep = false;
        deep = solve_deep_blocks() || deep;
        deep = solve_deep_lines() || deep;
        deep = solve_deep_columns() || deep;
    }

    blchPrint();
}


int main() {
//    vector<string> data = {
//        "53..7....",
//        "6..195...",
//        ".98....6.",
//        "8...6...3",
//        "4..8.3..1",
//        "7...2...6",
//        ".6....28.",
//        "...419..5",
//        "....8..79"
//    };

    vector<string> data = {"..9748...", "7........", ".2.1.9...", "..7...24.", ".64.1.59.", ".98...3..", "...8.3.2.",
                           "........6", "...2759.."};

    vector<vector<char>> board;
    for (auto str: data) {
        vector<char> chars;
        for (auto c: str) {
            chars.push_back(c);
        }
        board.push_back(chars);
    }

    cout << "Raw board:" << endl;
    boardPrint(board);
    cout << endl;

    solveSudoku(board);
    cout << "Solved:" << endl;
    boardPrint(board);

    cout << (isSolvedSudoku(board) ? "Solved!" : "Error!") << endl;

    return 0;
}
