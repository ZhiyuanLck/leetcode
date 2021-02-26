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
    int threeSumClosest(vector<int>& nums, int target) {
      int sum_closest = nums[0] + nums[1] + nums[2];
      int min_diff = abs( sum_closest - target);
      if (nums.size() == 3 ) { return sum_closest; }
      sort(nums.begin(), nums.end());
      auto it = nums.begin();
      vector<int>::iterator left, right;
      // cout << nums;
      for (; it < nums.end() - 2;) {
        // cout << *it << endl;
        if (3 * *it + 3 >= target) {
          int sum = *it + *(it + 1) + *(it + 2);
          int diff = abs(sum - target);
          return diff < min_diff ? sum : sum_closest;
        }
        left = it + 1;
        right = nums.end() - 1;
        while (left < right) {
          int sum = *it + *left + *right;
          // cout << "left: " << *left << endl;
          // cout << "right: " << *right << endl;
          // cout << "sum: " << sum << endl;
          if (sum == target) { return sum; }
          int diff = abs(sum - target);
          if (diff < min_diff) {
            sum_closest = sum;
            min_diff = diff;
          }
          if (sum < target) {
            for (int cur = *left; *left == cur && left < right; ++left);
          } else {
            for (int cur = *right; *right == cur && left < right; --right);
          }
        }
        for (int cur = *it; *it == cur && it < nums.end() - 2; ++it);
      }
      return sum_closest;
    }
};

int main() {
  vector<int> nums = {1,6,9,14,16,70};
  cout << Solution().threeSumClosest(nums, 81);
}
