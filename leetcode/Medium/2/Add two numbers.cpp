//
// Created by Gautham Banasandra on 20/09/18.
//

#include <cassert>
#include <iostream>

struct ListNode {
  explicit ListNode(int x) : val(x), next(nullptr) {}

  int val;
  ListNode *next;
};

class Solution {
 public:
  ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) const;
  static void PrintList(ListNode *head, const char *delimiter);

 private:
  ListNode *Add(ListNode *l1, ListNode *l2) const;
  void PropagateCarry(ListNode *l, ListNode *tail, bool carry) const;
};

ListNode *Solution::addTwoNumbers(ListNode *l1, ListNode *l2) const {
  return Add(l1, l2);
}

ListNode *Solution::Add(ListNode *l1, ListNode *l2) const {
  auto carry = false;
  ListNode *sum_head = nullptr, *sum_tail = nullptr;

  while (l1 != nullptr && l2 != nullptr) {
    auto sum = l1->val + l2->val + (carry ? 1 : 0);
    carry = sum > 9;

    auto sum_node = new ListNode(sum % 10);
    if (sum_head == nullptr && sum_tail == nullptr) {
      sum_head = sum_node;
    } else {
      assert(sum_head != nullptr && sum_tail != nullptr);
      sum_tail->next = sum_node;
    }

    sum_tail = sum_node;
    l1 = l1->next;
    l2 = l2->next;
  }

  PropagateCarry(l1 == nullptr ? l2 : l1, sum_tail, carry);
  return sum_head;
}

void Solution::PropagateCarry(ListNode *l, ListNode *tail, bool carry) const {
  tail->next = l;
  while (l != nullptr && carry) {
    auto sum = l->val + 1;
    carry = sum > 9;
    l->val = sum % 10;

    tail = l;
    l = l->next;
  }

  if (carry) {
    assert(l == nullptr);
    tail->next = new ListNode(1);
  }
}

void Solution::PrintList(ListNode *head, const char *delimiter = "") {
  while (head != nullptr) {
    std::cout << head->val << delimiter;
    head = head->next;
  }
  std::cout << std::endl;
}

int main() {
  auto l1 = new ListNode(2), l2 = new ListNode(5);
  auto p_l1 = l1, p_l2 = l2;

  p_l1->next = new ListNode(4);
  p_l1 = p_l1->next;
  p_l1->next = new ListNode(3);
  p_l1 = p_l1->next;

  p_l2->next = new ListNode(6);
  p_l2 = p_l2->next;
  p_l2->next = new ListNode(4);
  p_l2 = p_l2->next;

  Solution::PrintList(l1);
  Solution::PrintList(l2);

  auto sum = Solution().addTwoNumbers(l1, l2);
  Solution::PrintList(sum);
  return 0;
}