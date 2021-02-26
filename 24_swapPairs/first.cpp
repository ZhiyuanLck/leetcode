#include <iostream>
#include <vector>
#include <string>


using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
  ListNode* swapPairs(ListNode* head) {
    if (!head || !head->next) return head; // 特判
    auto l = head, r = head->next;
    ListNode* prev = nullptr;
    while (l && l->next) {
      auto r = l->next;
      if (prev) prev->next = r;
      l->next = r->next;
      r->next = l;
      if (!prev) head = r;
      prev = l;
      l = l->next;
    }
    return head;
  }
};

int main() {
  
}
