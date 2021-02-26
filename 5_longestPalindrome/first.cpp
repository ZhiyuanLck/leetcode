#include <iostream>
#include <vector>

using namespace std;

// template<template<class, class...> class T, class H, class... Args>
// ostream& operator<<(ostream &os, const T<H, Args...> &obj) {
  // bool start = true;
  // for (auto v: obj) {
    // if (start) {
      // os << v;
      // start = false;
    // }
    // else {
      // os << ' ' << v;
    // }
  // }
  // os << '\n';
  // return os;
// }

// dp

class Solution {
public:
    string longestPalindrome(string s) {
      if (s.size() < 2) return s;

      bool dp[s.size()][s.size()];
      for (int i = 0; i < s.size() ; ++i) dp[i][i] = true;
      int max_len = 1, start_pos = 0;

      for (size_t j = 1; j < s.size(); ++j) {
        for (size_t i = 0; i < j; ++i) {
          // (j - 1) - (i + 1) + 1 < 2 ==> j - i < 3
          if (s[i] != s[j]) {
            dp[i][j] = false;
            continue;
          }
          dp[i][j] = (j - i < 2 ? true : dp[i + 1][j - 1]);
          if (dp[i][j] && j - i + 1 > max_len) {
            max_len = j - i + 1;
            start_pos = i;
          }
        }
      }
      return s.substr(start_pos, max_len);
    }
};

int main() {
  string s = "aacabdkacaa";
  cout << Solution().longestPalindrome(s);
}
