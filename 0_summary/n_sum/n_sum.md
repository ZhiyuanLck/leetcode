# n数之和

## 问题描述

给定整数数组A[0], A[1], ..., A[N]，其中是否存在n个不同的元素a[0], a[1], ..., a[n-1]，它们的和为target，求出所有的解

## 思路

先对数组排序，然后从小到大确定满足条件的n个数。

遍历a[0]所有可能的值，不妨设a[0] = A[r]，0 <= r <= N - 1，
则问题转化为求有序数组A[r+1], A[r+2], ..., A[N-1]中的n - 1数之和为target - a[0] = target[0]的解。

当a[0], a[1], ..., a[n-i-1]的值都已经确定时，设a[n-i-1] = A[s]，
则问题转化为求有序数组A[s+1], A[s+2], ..., A[N-1]中的
i数之和为target - a[0] - ... - a[n-i-1] = target[n-i-1]的解，2 <= i <= n - 1。

最终可以转化为求有序数组中两数之和为target - a[0] - a[1] - ... - a[n-3]的解，用双指针法求解即可。

## 优化

假设此时问题为求i数之和，a[0], a[1], ..., a[n-i-1]的值已确定，对应数组为A[s+1], A[s+2], ..., A[N-1]

- 若对应数组长度小于i，**回溯到求i - 1数之和，迭代a[n-i-1]**
- 若A[s+1] + A[s+2] + ... + A[s+i] > target[n-i-1]，**回溯到求i - 1数之和，迭代a[n-i-1]**
- 若a[n-i] + A[N-i+1] + A[N-i+2] + A[N] < target[n-i-1]，**迭代a[n-i]**
- 迭代a[n-i]时，排除掉重复的元素

依此类推，当a[0], a[1], ..., a[n-3]
- 对数组排序
- 转为n-1数之和：迭代器it遍历数组，在it右侧的数组中求n-1数之和
- 最后求2数之和

## 2数之和

双指针遍历，left在最左侧，right在最右侧，比较此时的和与t，如果**`left < right`**则移动指针

- 小于t：往右移动left
- 大于t：往左移动right
- 等于t：同时移动两个指针

移动指针时排除掉重复的

## 代码实现

```cpp
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
```
