#include <iostream>
#include <vector>
#include <unordered_map>


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
  vector<int> twoSum(vector<int>& nums, int target) {
    unordered_map<int, int> hashmap;
    vector<int> result;
    int i = 0;
    for (const int& x : nums) {
      cout << x << endl;
      auto search = hashmap.find(target - x);
      if (search != hashmap.end()) {
        result = {i, hashmap[target - x]};
        return result;
      }
      else {
        hashmap[x] = i;
      }
      ++i;
    }
    return result;
  }
};

int main() {
  vector<int> nums = {2, 7};
  cout << Solution().twoSum(nums, 9);
  // unordered_map<int, int> hashmap;
  // cout << "134";
}
