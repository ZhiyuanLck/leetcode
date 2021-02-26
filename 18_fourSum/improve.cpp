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
      auto ite = nums.end();
      for (auto it1 = nums.begin(); it1 < ite - 3; ++it1) {
        // cout << "===== " << *it1 << endl;
        if (*it1 + *(it1 + 1) + *(it1 + 2) + *(it1 + 3) > target) break;
        // cout << "+++++" << endl;
        // remove duplicates
        // cout << "remove dup of it1\n";
        if (it1 != nums.begin() && *it1 == *(it1 - 1)) continue;
        // cout << "imporve two sum of it1\n";
        // improve two sum
        if (*it1 + *(ite - 3) + *(ite - 2) + *(ite - 1) < target) continue;
        for (auto it2 = it1 + 1; it2 < ite - 2; ++it2) {
          if (*it1 + *it2 + *(it2 + 1) + *(it2 + 2) > target) break;
          // remove duplicates
          // cout << "remove dup of it2\n";
          if (it2 != it1 + 1 && *it2 == *(it2 - 1)) continue;
          // improve two sum
          // cout << "imporve two sum of it2\n";
          if (*it1 + *it2 + *(ite - 2) + *(ite - 1) < target) continue;
          for (auto left = it2 + 1, right = ite - 1; left < right;) {
            int t = target - *it1 - *it2;
            int sum = *left + *right;
            // cout << sum << " " << t << endl;
            // cout << *it1 << " "
              // << *it2 << " "
              // << *left << " "
              // << *right << " = "
              // << sum + *it1 + *it2 << endl;
            auto move_left = [&left, &right]() {
              do { ++left; } while (left < right && *left == *(left - 1));
            };
            auto move_right = [&left, &right]() {
              do { --right; } while (left < right && *right == *(right + 1));
            };
            if (sum < t) {
              move_left();
            } else if (sum > t) {
              move_right();
            } else {
              result.push_back({*it1, *it2, *left, *right});
              move_left();
              move_right();
            }
          }
        }
      }
      return result;
    }
};

int main() {
  vector<int> nums = {-3,-1,0,2,4,5};
  nums = {-2,-1,-1,1,1,2,2};
  cout << Solution().fourSum(nums, 0);
}
