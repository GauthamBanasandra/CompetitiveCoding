#include "ListNode.h"

#include <string>
#include <vector>

#include "gtest/gtest.h"

// Defined in "Remove nth Node from End of List.cpp"
ListNode *RemoveNthLastNode(ListNode *head, int n);

namespace {

ListNode *BuildList(const std::vector<int> &vals) {
  ListNode *head = nullptr;
  ListNode *tail = nullptr;
  for (int v : vals) {
    auto *node = new ListNode(v);
    if (head == nullptr) {
      head = node;
      tail = node;
    } else {
      tail->next = node;
      tail = node;
    }
  }
  return head;
}

std::vector<int> ToVector(ListNode *head) {
  std::vector<int> out;
  while (head != nullptr) {
    out.push_back(head->val);
    head = head->next;
  }
  return out;
}

struct RemoveNthCase {
  std::string name;
  std::vector<int> input;
  int n;
  std::vector<int> expected;
};

void PrintTo(const RemoveNthCase &c, std::ostream *os) { *os << c.name; }

class RemoveNthLastNodeTest : public testing::TestWithParam<RemoveNthCase> {};

TEST_P(RemoveNthLastNodeTest, RemovesExpectedNode) {
  const RemoveNthCase &c = GetParam();
  ListNode *head = BuildList(c.input);
  ListNode *result = RemoveNthLastNode(head, c.n);
  EXPECT_EQ(ToVector(result), c.expected);
}

// Valid inputs per the problem constraints: list has >= 1 node and 1 <= n <= len.
INSTANTIATE_TEST_SUITE_P(
    ValidInputs, RemoveNthLastNodeTest,
    testing::Values(
        RemoveNthCase{"remove_middle_n2", {1, 2, 3, 4, 5}, 2, {1, 2, 3, 5}},
        RemoveNthCase{"remove_last_n1", {1, 2, 3, 4, 5}, 1, {1, 2, 3, 4}},
        RemoveNthCase{"remove_head_n_equals_len", {1, 2, 3, 4, 5}, 5, {2, 3, 4, 5}},
        RemoveNthCase{"two_nodes_remove_head_n2", {1, 2}, 2, {2}},
        RemoveNthCase{"two_nodes_remove_tail_n1", {1, 2}, 1, {1}},
        RemoveNthCase{"single_node_n1", {1}, 1, {}},
        RemoveNthCase{"remove_head_of_three_n3", {7, 8, 9}, 3, {8, 9}},
        RemoveNthCase{"long_list_interior_n6",
                      {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
                      6,
                      {1, 2, 3, 4, 6, 7, 8, 9, 10}},
        RemoveNthCase{"long_list_remove_head_n_len",
                      {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
                      10,
                      {2, 3, 4, 5, 6, 7, 8, 9, 10}},
        RemoveNthCase{"duplicate_values_n2", {5, 5, 5, 5}, 2, {5, 5, 5}},
        RemoveNthCase{"remove_second_from_head_n_len_minus_1",
                      {1, 2, 3, 4, 5},
                      4,
                      {1, 3, 4, 5}}),
    [](const testing::TestParamInfo<RemoveNthCase> &info) {
      return info.param.name;
    });

}  // namespace
