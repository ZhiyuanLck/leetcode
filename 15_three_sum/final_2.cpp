#include <iostream>
#include <vector>
#include <unordered_map>
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
    vector<vector<int>> threeSum(vector<int>& nums) {
      vector<vector<int>> result;
      if (nums.size() < 3) {
        return result;
      }
      sort(nums.begin(), nums.end());
      for (auto i = 0; i < nums.size() - 2;) {
        if (nums[i] > 0) {
          return result;
        }
        if (nums[i] == 0) {
          if (i + 2 < nums.size() && nums[i + 2] == 0) {
            result.push_back({0, 0, 0});
          }
          return result;
        }
        for (int j = i + 1, k = nums.size() - 1; j < k;) {
          int sum = nums[i] + nums[j] + nums[k];
          // cout << nums.size() << endl;
          // cout << "i: " << i << "\t"
            // << "j: " << j << "\t"
            // << "k: " << k << "\t"
            // << "sum: " << sum << endl;
          if (sum <= 0) {
            if (sum == 0) {
              result.push_back({nums[i], nums[j], nums[k]});
            }
            for (auto cur = nums[j]; nums[j] == cur && j < k; ++j) {}
          }
          else {
            for (auto cur = nums[k]; nums[k] == cur && j < k; --k) {}
          }
        }
        for (auto cur = nums[i]; nums[i] == cur && i < nums.size(); ++i) {}
      }
      return result;
    }
};

int main() {
  // vector<int> nums = {-4,-2,1,-5,-4,-4,4,-2,0,4,0,-2,3,1,-5,0};
  vector<int> nums = {-1,0,1,2,-1,-4};
  nums = {3,0,-2,-1,1,2};
  nums = {0, 0, 0, 0};
  nums = {2,0,-2,-5,-5,-3,2,-4};
  cout << Solution().threeSum(nums);
}
