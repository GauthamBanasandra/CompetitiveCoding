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

size_t ListManager::GetLength() {
  size_t len = 0;
  auto head = head_;

  while (head != nullptr) {
    ++len;
    head = head->next;
  }

  return len;
}

void ListManager::DeleteNextNode(ListNode *prevNode) {
  if (prevNode == nullptr || prevNode->next == nullptr) {
    return;
  }

  auto nodeToDel = prevNode->next;
  prevNode->next = nodeToDel->next;
  nodeToDel->next = nullptr;
}

ListNode *ListManager::DeleteAndGetNewHead() {
  auto nodeToDel = head_;
  if (head_ == nullptr) {
    return nullptr;
  }

  head_ = head_->next;
  nodeToDel->next = nullptr;
  return head_;
}

ListNode *ListManager::RemoveNthLastNode(int n) {
  const auto len = GetLength();
  auto nodeToDel = head_;
  ListNode *prevNode = nullptr;

  for (size_t i = 1; i <= len - static_cast<size_t>(n); ++i) {
    prevNode = nodeToDel;
    nodeToDel = nodeToDel->next;
  }

  if (prevNode == nullptr) {
    return DeleteAndGetNewHead();
  }

  DeleteNextNode(prevNode);
  return head_;
}

ListNode *RemoveNthLastNode(ListNode *head, int n) {
  ListManager listMgr(head);
  return listMgr.RemoveNthLastNode(n);
}
