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
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
      auto &a = nums1, &b = nums2;
      auto m = a.size(), n = b.size();
      // 排除空数组
      if (!m) return (n - 1) & 1 ? double(b[(n - 2) / 2] + b[n / 2]) / 2 : b[(n - 1) / 2];
      if (!n) return (m - 1) & 1 ? double(a[(m - 2) / 2] + a[m / 2]) / 2 : a[(m - 1) / 2];
      // 排除单边median
      auto another = [](vector<int>& nums, size_t idx, int cmp, bool is_left) -> double {
        if (is_left ? idx + 1 >= nums.size() : idx - 1 < 0) return cmp;
        return double(is_left ? min(nums[idx + 1], cmp) : max(nums[idx - 1], cmp));
      };
      size_t sum = m + n - 1;
      bool even = bool(sum & 1);
      size_t k1 = even ? (sum - 1) / 2 : sum / 2 - 1;
      size_t k2 = even ? (sum + 1) / 2 : sum / 2 + 1;
      // median <= a[0]
      if (k1 < n && b[k1] <= a[0]) {
        // cout << "median <= a[0] = " << a[0] << endl;
        if (b[k1] == a[0]) return a[0];
        if (even) return (b[k1] + another(b, k1, a[0], true)) / 2;
        return another(b, k1, a[0], true);
      }
      // median <= b[0]
      if (k1 < m && a[k1] <= b[0]) {
        // cout << "median <= b[0] = " << b[0] << endl;
        if (a[k1] == b[0]) return b[0];
        if (even) return (a[k1] + another(a, k1, b[0], true)) / 2;
        return another(a, k1, b[0], true);
      }
      // median >= a[m - 1]
      if (k2 >= m && b[k2 - m] >= a[m - 1]) {
        // cout << "median >= a[m - 1] = " << a[m - 1] << endl;
        if (b[k2 - m] == a[m - 1]) return a[m - 1];
        if (even) return (b[k2 - m] + another(b, k2 - m, a[m - 1], false)) / 2;
        return another(b, k2 - m, a[m - 1], false);
      }
      // median >= b[n - 1]
      if (k2 >= n && a[k2 - n] >= b[n - 1]) {
        // cout << "median >= b[n - 1] = " << b[n - 1] << endl;
        if (a[k2 - n] == b[n - 1]) return b[n - 1];
        if (even) return (a[k2 - n] + another(a, k2 - n, b[n - 1], false)) / 2;
        return another(a, k2 - n, b[n - 1], false);
      }
      // main loop
      size_t l1 = 0, l2 = 0, r1 = m - 1, r2 = n - 1;
      auto total = even ? (m + n) / 2 + 1 : (m + n + 1) / 2;
      size_t mid1 = r1 / 2, mid2 = total - mid1 - 2;
      auto d = [&r1, &r2, &l1, &l2]() { return (min(r1 - l1, r2 - l2) + 1) / 2; };
      auto median = [even](int a, int b) { return even ? double(a + b) / 2 : max(a, b); };
      while (1) {
        // cout << "l r\n" << l1 << " " << r1 << " " << l2 << " " << r2 << endl;
        // cout << a[mid1] << " " << b[mid2] << endl;
        if (a[mid1] == b[mid2]) return a[mid1]; // 优化
        if (a[mid1] > b[mid2]) {
          if (b[mid2 + 1] >= a[mid1]) {
            if (!even) return max(a[mid1], b[mid2]);
            return median(max(a[mid1 - 1], b[mid2]), a[mid1]);
          }
          r1 = mid1;
          l2 = mid2;
          mid1 -= d();
          mid2 += d();
        } else { // a[mid1] < b[mid2]
          if (a[mid1 + 1] >= b[mid2]) {
            if (!even) return max(a[mid1], b[mid2]);
            return median(max(b[mid2 - 1], a[mid1]), b[mid2]);
          }
          l1 = mid1;
          r2 = mid2;
          mid1 += d();
          mid2 -= d();
        }
      }
    }
};

int main() {
  vector<int> a, b;
  a = {1,7};
  b = {2,3,4,5,6,8};
  cout << Solution().findMedianSortedArrays(a, b);
  // cout << (1 + double(2))/2 << endl;
}
