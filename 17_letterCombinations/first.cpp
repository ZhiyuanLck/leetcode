#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*
 * 回溯：子串遍历完了
 */

// const unordered_map<char, string> dict = {
  // {'2', "abc"}, {'3', "def"}, {'4', "ghi"}, {'5', "jkl"},
  // {'6', "mno"}, {'7', "pqrs"}, {'8', "tuv"}, {'9', "wxyz"}
// };
const string s = "abcdefghijklmnopqrstuvwxyz";

class Solution {
public:
  vector<string> letterCombinations(string digits) {
    if (digits.empty()) return {};
    vector<size_t> bounds = {0, 3, 6, 9, 12, 15, 19, 22, 26};
    vector<size_t> manager(digits.size());
    manager[0] = bounds[digits[0] - '2'];
    vector<string> result;
    string record;
    size_t i = 0;
    for (size_t i = 0;; ++manager[i]) {
      // cout << i << endl;
      // 当前数字遍历完，回溯
      if (manager[i] == bounds[digits[i] - '2' + 1]) {
        if (i == 0) break;
        // cout << "当前数字遍历完，回溯\n";
        record.pop_back();
        --i;
        continue;
      }
      // 记录
      record.push_back(s[manager[i]]);
      // push到result
      if (i == digits.size() - 1) {
        // cout << "记录结果\n";
        result.push_back(record);
        record.pop_back();
        continue;
      }
      // 下一个数字
      // cout << "下一个数字\n";
      ++i;
      manager[i] = bounds[digits[i] - '2'];
      --manager[i];
    }
    // for (auto const& x : result) cout << x << " ";
    return result;
  }
};

int main() {
  string s = "23";
  Solution().letterCombinations(s);
}
