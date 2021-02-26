#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
// #include <utility>


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
      unordered_set<int> searched, found;
      unordered_map<int, vector<int>> head;
      vector<vector<int>> result;
      int cur = 0;
      for (auto const& x : nums) {
        // cout << "======\npos: " << cur << endl;
        // cout << "x: " << x << endl;
        // num | true for usable, false for used
        unordered_map<int, bool> twosum;
        auto search_searched_x = searched.find(x);
        // not find in searched, process twosum
        if (search_searched_x == searched.end()) {
          int i = 0;
          bool is_found = false;
          // cout << "Not found in done, processing" << endl;
          for (auto const& y : nums) {
            // cout << "i: " << i << endl;
            if (i != cur) {
              auto search_twosum_z = twosum.find(-x - y);
              // 寻找两数之和，首位相同不重复
              if (search_twosum_z != twosum.end() && search_twosum_z->second) {
                // 去重
                auto search_found_y = found.find(y);
                auto search_found_z = found.find(-x - y);
                // 首位不同的重复
                if (search_found_y == found.end() && search_found_z == found.end()) {
                  is_found = true;
                  search_twosum_z->second = false;
                  // cout << "found" << endl;
                  result.push_back({x, y, -x - y});
                }
                twosum[y] = false;
              }
              else {
                auto search_twosum_y = twosum.find(y);
                if (search_twosum_y == twosum.end()) {
                  twosum[y] = true;
                }
              }
            }
            ++i;
          }
          if (is_found) {
            found.insert(x);
          }
          searched.insert(x);
        }
        ++cur;
      }
      return result;
    }
};

int main() {
  vector<int> nums = {-4,-2,1,-5,-4,-4,4,-2,0,4,0,-2,3,1,-5,0};
  // vector<int> nums = {0, 0, 0, 0};
  cout << Solution().threeSum(nums);
}
