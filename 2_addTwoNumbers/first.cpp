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

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
      int remainder = 0, sum;
      auto result = l1;
      auto set_val = [&remainder, &l1](int sum) {
        remainder = sum > 9 ? 1 : 0;
        l1->val = sum > 9 ? sum - 10 : sum;
      };
      while (l1 && l2) {
        set_val(l1->val + l2->val + remainder);
        if (!l1->next && !l2->next && remainder) {
          l1->next = new ListNode(1, nullptr);
          return result;
        }
        if (!l1->next) {
          l1->next = l2->next;
          l2->next = nullptr;
        }
        l1 = l1->next;
        l2 = l2->next;
      }
      // add remain
      while (l1 && remainder) {
        set_val(l1->val + remainder);
        if (l1->next) l1 = l1->next;
        else break;
      }
      // add carry
      if (remainder) {
        l1->next = new ListNode(1, nullptr);
      }
      return result;
    }
};

int main() {
  
}
