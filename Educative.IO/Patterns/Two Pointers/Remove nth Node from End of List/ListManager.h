#include "ListNode.h"

class ListManager {
public:
  ListManager(ListNode *head) { head_ = head; };
  size_t GetLength();
  void DeleteNextNode(ListNode *prevNode);
  ListNode *DeleteAndGetNewHead();
  ListNode *RemoveNthLastNode(int n);

private:
  ListNode *head_;
};
