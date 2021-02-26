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
  ListNode* removeNthFromEnd(ListNode* head, int n) {
    auto ans = head, ptr = head;
    ListNode* prev = nullptr;
    while (n--) head = head->next;
    while (head) {
      if (!head->next) prev = ptr;
      head = head->next;
      ptr = ptr->next;
    }
    if (!prev) return ans->next;
    prev->next = ptr->next;
    return ans;
  }
};

int main() {
  
}
