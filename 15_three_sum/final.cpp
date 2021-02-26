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
      unordered_map<int, int> num_freq;
      vector<int> uniq_nums;
      bool start = true;
      int prev_num = 0;
      for (auto const& x : nums) {
        // num_freq
        auto search = num_freq.find(x);
        if (search != num_freq.end()) {
          ++search->second;
        } else {
          num_freq[x] = 1;
        }
        // uniq_nums
        if (start) {
          start = false;
          uniq_nums.push_back(x);
        } else if (x != prev_num) {
          uniq_nums.push_back(x);
        }
        prev_num = x;
      }
      // cout << uniq_nums;
      for (auto const& n : uniq_nums) {
        if (n == 0) {
          auto search_zero = num_freq.find(0);
          if (search_zero != num_freq.end() && num_freq[0] >= 3) {
            result.push_back({0, 0, 0});
            return result;
          }
        } else if (n > 0) {
          return result;
        } else {
          auto valid_y = [&](int val){return max({0, -n/2}) <= val && val <= uniq_nums.back();};
          // cout << "===== n: " << n << endl;
          for (auto it = uniq_nums.rbegin(); it != uniq_nums.rend() && valid_y(*it); ++it) {
            int x = -n - *it;
            // cout << "-n/2: " << -n/2 << "\t"
              // << "y_max: " << uniq_nums.back() << "\t"
              // << "x: " << x << "\t"
              // << "y: " << *it << "\t"
              // << endl;
            // 不能再向左移动了
            if (x <= *it && x >= n) {
              // 相同元素
              if (x == n || x == *it) {
                if (num_freq[x] > 1) {
                  result.push_back({n, x, *it});
                }
              } else { // 正常情况
                auto search_x = num_freq.find(-n - *it);
                if (search_x != num_freq.end()) {
                  result.push_back({n, x, *it});
                }
              }
            }
          }
        }
      }
      return result;
    }
};

int main() {
  // vector<int> nums = {-4,-2,1,-5,-4,-4,4,-2,0,4,0,-2,3,1,-5,0};
  vector<int> nums = {-1,0,1,2,-1,-4};
  // nums = {3,0,-2,-1,1,2};
  cout << Solution().threeSum(nums);
}
