#include <iostream>
#include <vector>
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
      bool charmap[95] = {};
      auto dup = [&charmap, &s](size_t i) { return charmap[s[i] - ' ']; };
      auto change = [&charmap, &s](size_t i) { charmap[s[i] - ' '] = !charmap[s[i] - ' ']; };
      size_t l = 0, n = 0;
      for (size_t r = 0; r < s.size(); ++r) {
        if (dup(r)) {
          while (s[l] != s[r]) change(l++);
          change(l++);
        }
        change(r);
        n = max(n, r - l + 1);
      }
      return n;
    }
};

int main() {
  string s = "tmmzuxt";
  cout << Solution().lengthOfLongestSubstring(s);
}
