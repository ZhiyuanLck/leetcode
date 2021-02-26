#include <iostream>
#include <vector>


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
    int removeDuplicates(vector<int>& nums) {
      if (nums.empty()) {
        return 0;
      }
      int l = 0, r, mid;
      int cur_pos = 0;
      int first = 0;
      bool start = true;
      while (nums[cur_pos] != nums.back()) {
        r = nums.size() - 1;
        while (l < r) {
          mid = (l + 1 + r) / 2;
          if (nums[mid] == nums[cur_pos]) {
            l = mid;
          }
          else if (nums[mid - 1] == nums[cur_pos]) {
            nums[++cur_pos] = nums[mid];
            l = mid;
            break;
          }
          else {
            r = mid;
          }
        }
      }
      return cur_pos + 1;
    }
};

int main() {
  vector<int> nums = {1, 1, 2, 2, 3, 3, 3, 4};
  Solution().removeDuplicates(nums);
  cout << nums;
}
