#include <iostream>
#include <vector>
#include <algorithm>

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
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
      if (nums.size() < 4) return {};
      sort(nums.begin(), nums.end());
      vector<vector<int>> result;
      for (auto it4 = nums.begin(); it4 < nums.end() - 3;) {
        if (4 * *it4 > target) return result;
        for (auto it3 = it4 + 1; it3 < nums.end() - 2;) {
          // cout << *it3 << endl;
          if (3 * *it3 > target - *it4) break;
          for (auto left = it3 + 1, right = nums.end() - 1; left < right;) {
            int sum = *it4 + *it3 + *left + *right;
            // cout << *it4 << " "
              // << *it3 << " "
              // << *left << " "
              // << *right << " = "
              // << sum << endl;
            if (sum <= target) {
              if (sum == target) {
                result.push_back({*it4, *it3, *left, *right});
              }
              for (auto cur = *left; cur == *left && left < right; ++left) {}
            } else {
              for (auto cur = *right; cur == *right && left < right; --right) {}
            }
          }
          // cout << *it3 << endl;
          for (auto cur = *it3; cur == *it3 && it3 < nums.end() - 2; ++it3) {}
          // cout << *it3 << endl;
        }
        for (auto cur = *it4; cur == *it4 && it4 < nums.end() - 3; ++it4) {}
      }
      return result;
    }
};

int main() {
  vector<int> nums = {1,0,-1,0,-2,2};
  cout << Solution().fourSum(nums, 0);
}
