#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution {
public:
  vector<string> generateParenthesis(int n) {
    vector<string> ans = {""};
    vector<int> ans_l = {n}; // 对应模式剩余左括号的数量
    vector<int> ans_r = {n}; // 对应模式剩余右括号的数量
    for (size_t i = 0; i < 2 * n; ++i) { // 遍历2n个位置
      auto len = ans.size();
      for (size_t j = 0; j < len; ++j) { // 遍历之前的结果
        if (ans_l[j]) {
          ans.push_back(ans[j] + '(');
          ans_l.push_back(ans_l[j] - 1);
          ans_r.push_back(ans_r[j]);
        }
        // 剩余的右括号数量要大于剩余的左括号的数量
        if (ans_r[j] && ans_r[j] > ans_l[j]) {
          ans.push_back(ans[j] + ')');
          ans_l.push_back(ans_l[j]);
          ans_r.push_back(ans_r[j] - 1);
        }
      }
      ans.erase(ans.begin(), ans.begin() + len);
      ans_l.erase(ans_l.begin(), ans_l.begin() + len);
      ans_r.erase(ans_r.begin(), ans_r.begin() + len);
    }
    // for (auto x : ans) cout << x << endl;
    return ans;
  }
};

int main() {
  Solution().generateParenthesis(3);
}
