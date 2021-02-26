#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>

using namespace std;

template<template<class, class...> class T, class H, class... Args>
ostream& operator<<(ostream &os, const T<H, Args...> &obj) {
  bool start = true;
  for (auto v: obj) {
    if (start) {
      os << v;
      start = false;
    }
    else {
      os << ' ' << v;
    }
  }
  os << '\n';
  return os;
}

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
      if (s.size() < 2) return s.size();
      size_t l = 0, n = 0;
      unordered_map<char, size_t> charmap;
      for (auto r = 0; r < s.size(); ++r) {
        auto search = charmap.find(s[r]);
        if (search != charmap.end()) {
          auto saved_pos = search->second;
          for (int i = l; i <= saved_pos; ++i) {
            charmap.erase(s[i]);
          }
          l = saved_pos + 1;
        }
        charmap[s[r]] = r;
        n = max(n, r - l + 1);
      }
      return n;
    }
};

int main() {
  string s = "abcabcbb";
  cout << Solution().lengthOfLongestSubstring(s);
}
