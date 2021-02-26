#include <iostream>
#include <vector>
#include <string>
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

/*
 * 如果末两位a[n - 2] < a[n - 1]交换即可
 * 如果是逆序，返回正序
 * 从后往前遍历，找到a[i]使得a[i] < a[i + 1]且a[i + 1] >= a[i + 2] >= ... >= a[n - 1]
 * 翻转[i + 1, n - 1]范围内的数组，并找到j使得a[j] = min{a[k] | a[k] > a[i], i < k < n}
 * 交换j与i处的元素
 */
class Solution {
public:
  void nextPermutation(vector<int>& nums) {
    if (nums.size() < 2) return;
    auto it = nums.end() - 1;
    if (*(it - 1) < *it) {
      iter_swap(it - 1, it);
      return;
    }
    while (it > nums.begin() && *(it - 1) >= *it) --it;
    if (it == nums.begin()) {
      reverse(nums.begin(), nums.end());
      return;
    }
    auto l = it - 1;
    if (*l < nums.back()) { // 特判，防止判断*it > *l越界
      iter_swap(l, nums.rbegin());
    }
    else {
      while (*it > *l) ++it;
      iter_swap(l, it - 1);
    }
    reverse(l + 1, nums.end());
  }
};

int main() {
  vector<int> nums = {3, 2};
  nums = {1, 3, 2};
  nums = {0,4,2,0,3,3,3,3};
  // for (auto const& x : nums) cout << &x << endl;
  Solution().nextPermutation(nums);
  cout << nums;
}
