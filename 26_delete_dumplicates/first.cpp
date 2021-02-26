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
      int cur_pos = 0;
      int last;
      bool start = true;
      for (auto const& x : nums) {
        if (start) {
          start = false;
          last = x;
        }
        else if (x != last) {
          nums[++cur_pos] = x;
          last = x;
        }
      }
      return start ? 0 : cur_pos + 1;
    }
};

int main() {
  vector<int> nums = {};
  Solution().removeDuplicates(nums);
  cout << nums;
}
