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
      sort(nums.begin(), nums.end());
      // cout << nums;
      // number : frequency
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
      // algorithms begin
      vector<vector<int>> result;
      if (nums.empty()) {
        return result;
      }
      auto search = num_freq.find(0);
      if (search != num_freq.end() && search->second >= 3) {
        result.push_back({0, 0, 0});
      }
      auto l = uniq_nums.begin(), r = uniq_nums.end() - 1;
      while (l != r) {
        // cout << "Next loop..."
          // << "l: " << *l << "\t"
          // << "r: " << *r << "\t"
          // << endl;
        if (-*l - *r >= *l) {
          // cout << "Exclude right val" << endl;
          for (auto l_cur = l; l_cur != r; ++l_cur) {
            int z = -*l_cur - *r;
            bool is_find = false;
            if (z == *l_cur || z == *r) {
              if (num_freq[z] > 1) {
                is_find = true;
              }
            } else {
              auto search = num_freq.find(z);
              if (search != num_freq.end() && search->first > *l_cur && search->first < *r) {
                is_find = true;
              }
            }
            if (is_find) {
              result.push_back({*l_cur, z, *r});
            }
          }
          --r;
        } else {
          for (auto r_cur = r; r_cur != l; --r_cur) {
            int z = -*l - *r_cur;
            bool is_find = false;
            if (z == *l || z == *r_cur) {
              if (num_freq[z] > 1) {
                is_find = true;
              }
            } else {
              auto search = num_freq.find(z);
              if (search != num_freq.end() && search->first > *l && search->first < *r_cur) {
                is_find = true;
              }
            }
            if (is_find) {
              result.push_back({*l, z, *r_cur});
            }
          }
          ++l;
        }
      }
      return result;
    }
};

int main() {
  // vector<int> nums = {-4,-2,1,-5,-4,-4,4,-2,0,4,0,-2,3,1,-5,0};
  vector<int> nums = {-1,0,1,2,-1,-4};
  cout << Solution().threeSum(nums);
}
