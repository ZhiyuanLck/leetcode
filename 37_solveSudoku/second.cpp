#include <iostream>
#include <vector>
#include <string>
#include <bitset>

using namespace std;

class Solution {
public:
  using Int = unsigned short;
  void solveSudoku(vector<vector<char>>& board) {
    bool row_check[9][9] = {}, col_check[9][9] = {}, block_check[9][9] = {};
    vector<Int> unfilled;
    vector<Int> ans;
    for (size_t i = 0; i < 9; ++i) {
      for (size_t j = 0; j < 9; ++j) {
        if (board[i][j] != '.') {
          Int n = board[i][j] - '1';
          row_check[i][n] = true;
          col_check[j][n] = true;
          block_check[i / 3 * 3 + j / 3][n] = true;
        }
        else {
          unfilled.push_back(i * 9 + j);
        }
      }
    }
    auto set = [&unfilled, &row_check, &col_check, &block_check](size_t k, Int n, bool status) {
      Int i = unfilled[k] / 9, j = unfilled[k] % 9, b = i / 3 * 3 + j / 3;
      row_check[i][n] = status;
      col_check[j][n] = status;
      block_check[b][n] = status;
    };
    size_t n = 0;
    for (size_t k = 0; k < unfilled.size();) {
      Int i = unfilled[k] / 9, j = unfilled[k] % 9, b = i / 3 * 3 + j / 3;
      for (; n < 9; ++n) {
        if (!row_check[i][n] && !col_check[j][n] && !block_check[b][n]) {
          ans.push_back(n);
          set(k, n, true);
          break;
        }
      }
      if (n == 9) {
        if (k == 0) {
          cout << "NO ANSWER!\n";
          return;
        }
        n = ans.back();
        ans.pop_back();
        --k;
        set(k, n, false);
        ++n;
      }
      else {
        n = 0;
        ++k;
      }
    }
    for (size_t k = 0; k < unfilled.size(); ++k) {
      board[unfilled[k] / 9][unfilled[k] % 9] = char(ans[k] + '1');
    }
  }
};

int main() {
  vector<vector<char>> board = {
  {'5','3','.','.','7','.','.','.','.'},{'6','.','.','1','9','5','.','.','.'},{'.','9','8','.','.','.','.','6','.'},{'8','.','.','.','6','.','.','.','3'},{'4','.','.','8','.','3','.','.','1'},{'7','.','.','.','2','.','.','.','6'},{'.','6','.','.','.','.','2','8','.'},{'.','.','.','4','1','9','.','.','5'},{'.','.','.','.','8','.','.','7','9'}
  };
  Solution().solveSudoku(board);
}
