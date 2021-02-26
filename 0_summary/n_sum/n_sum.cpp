#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

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

typedef vector<vector<int>::iterator> Manager;

class Solution {
public:
  vector<vector<int>> nSum(vector<int> &nums, int target, int n) {
    if (nums.size() < n) return {}; // 特判，数组长度小于n时返回空
    sort(nums.begin(), nums.end()); // 数组排序

    Manager iters(n - 1, nums.begin()); // 指针数组
    vector<vector<int>> result; // 返回值
    vector<int> record; // 记录栈
    int cur_n = n; // 当前所求的是几数之和

    // 当求完i数和（1. 遍历完；2. 从**it开始的i个数大于target）后，回溯到求i+1数和
    auto back = [&record, &target](Manager::iterator &it) {
      target += record.back();
      record.pop_back();
      --it;
    };

    for (auto it = iters.begin();; ++*it) {
      cur_n = n - record.size(); // 当前所求为cur_n数之和

      // cur_n数之和遍历完，回溯
      if (*it > nums.end() - cur_n) {
        if (cur_n == n) break;
        back(it);
        continue;
      }

      // 剪枝，排除不可能的情况
      if (accumulate(*it, *it + cur_n, 0) > target) {
        if (cur_n == n) break; // 直接返回结果
        back(it);
        continue;
      }

      // 求2数之和
      if (cur_n == 2) {
        for (auto left = *it, right = nums.end() - 1; left < right;) {
          int sum = *left + *right;
          if (sum < target) {
            do { ++left; } while (left < right && *left == *(left - 1));
          } else if (sum > target) {
            do { --right; } while (left < right && *right == *(right + 1));
          } else {
            record.push_back(*left);
            record.push_back(*right);
            result.push_back(record);
            record.pop_back();
            record.pop_back();
            do { ++left; } while (left < right && *left == *(left - 1));
            do { --right; } while (left < right && *right == *(right + 1));
          }
        }
        back(it);
        continue;
      }

      // 去重
      auto start = cur_n == n ? *it == nums.begin() : *it == *(it - 1) + 1;
      if (!start && **it == *(*it - 1)) continue;

      // 优化，设当前求i数之和，从nums中从右往左选取i-1个数，计算i数之和，如果小于targe则右移it
      if (**it + accumulate(nums.end() - cur_n + 1, nums.end(), 0) < target) continue;

      // 由求cur_n数之和转换为求cur_n - 1数之和
      record.push_back(**it);
      target -= **it; // 记录当前选取的数
      ++it; // 右移it
      *it = *(it - 1); // 初始化下轮迭代的it
    }
    return result;
  }
};

int main() {
  vector<int> nums = {-3,-1,0,2,4,5};
  nums = {0, 0, 0, 0};
  cout << Solution().nSum(nums, 0, 4);
}
