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
    int maxArea(vector<int>& height) {
      int l = 0, r = height.size() - 1;
      int max_area = (r - l) * min(height[l], height[r]);
      while (l < r) {
        if (height[l] <= height[r]) {
          ++l;
        }
        else {
          --r;
        }
        max_area = max(max_area, (r - l) * min(height[l], height[r]));
      }
      return max_area;
    }
};

int main() {
  
}
