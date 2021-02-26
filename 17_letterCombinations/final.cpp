#include <iostream>
#include <vector>
#include <string>


using namespace std;

// 使用队列，队列当前存储的结果为遍历过的数字对应的字母组合
// 遍历新数字时，用之前的结果与当前数字对应的字母进行组合，得到新结果然后删除旧结果
const string M[8] = {"abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
class Solution {
public:
  vector<string> letterCombinations(string digits) {
    if (digits.empty()) return {};
    vector<string> ans = {""}; // 之前结果为空串
    for (auto const& ch : digits) { // 遍历数字
      auto len = ans.size(); // 记录末尾
      for (size_t i = 0; i < len; ++i) { // 遍历之前结果
        for (auto const& cur : M[ch - '2']) { // 组合当前字母与之前的结果
          ans.push_back(ans[i] + cur);
        }
      }
      ans.erase(ans.begin(), ans.begin() + len);
    }
    return ans;
  }
};

int main() {
  string s = "23";
  Solution().letterCombinations(s);
}
