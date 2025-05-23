//
// Created by gauth on 25-02-2018.
//

#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <memory>
#include <cassert>
#include <functional>

using ui = unsigned int;
using ul = unsigned long;

namespace ds {
namespace bin_tree {
enum class node_type { k_left_child, k_right_child, k_root };

template<typename T>
class node {
 public:
  explicit node(T &data, node_type type) : type(type), ancestor(nullptr), left_child(nullptr),
                                           right_child(nullptr), height(1), data(data) {
  }

  bool is_leaf() { return left_child == nullptr && right_child == nullptr; }
  void copy_data_to(node<T> *other) { other->data = this->data; }
  static void remove(node<T> *&n);

  node_type type;
  node<T> *ancestor;
  node<T> *left_child;
  node<T> *right_child;
  long long height;
  T data;
};

template<typename T>
void node<T>::remove(node<T> *&n) {
  n->left_child = n->right_child = nullptr;
  auto &ancestor = n->ancestor;
  switch (n->type) {
    case node_type::k_left_child:ancestor->left_child = nullptr;
      break;

    case node_type::k_right_child:ancestor->right_child = nullptr;
      break;

    case node_type::k_root:break;

    default:
      // Unhandled node type
      assert(false);
  }

  delete n;
  n = nullptr;
}
}
}

namespace ds {
namespace bin_tree {
template<class T>
struct node_info {
  T *key;
  node<T> *ancestor;
  node_type type;
};

template<class T>
class binary_tree {
  using big_int = unsigned long long;

 public:
  explicit binary_tree() : root(nullptr) {}

  // Traversal methods with visit_action as a lambda
  void preorder(std::function<void(node<T> *n)> visit_action = [](node<T> *n) -> void {
    std::cout << n->data << '\n';
  });
  void postorder(std::function<void(node<T> *n)> visit_action = [](node<T> *n) -> void {
    std::cout << n->data << '\n';
  });
  void inorder(std::function<void(node<T> *n)> visit_action = [](node<T> *n) -> void { std::cout << n->data << '\n'; });

  // C++ doesn't allow a member to be used as the default value (for node as root)
  // Thus, we need expose traversal methods as wrappers of these functions
  void preorder(node<T> *n, std::function<void(node<T> *)> &&visit_action);
  void postorder(node<T> *n, std::function<void(node<T> *)> &&visit_action);
  void inorder(node<T> *n, std::function<void(node<T> *)> &&visit_action);
  long long height();
  static long long height(node<T> *n);

 protected:
  // A utility function to get the height of the node
  static long long get_height(node<T> *n) { return n == nullptr ? 0 : n->height; }
  void replace(node<T> *&current, node<T> *other);

 public:
  node<T> *root;
};

template<class T>
void binary_tree<T>::preorder(std::function<void(node<T> *n)> visit_action) {
  preorder(root, std::move(visit_action));
}

template<class T>
void binary_tree<T>::postorder(std::function<void(node<T> *n)> visit_action) {
  postorder(root, std::move(visit_action));
}

template<class T>
void binary_tree<T>::inorder(std::function<void(node<T> *n)> visit_action) {
  inorder(root, std::move(visit_action));
}

template<class T>
void binary_tree<T>::preorder(node<T> *n, std::function<void(node<T> *)> &&visit_action) {
  if (n == nullptr) {
    return;
  }

  visit_action(n);
  preorder(n->left_child, std::move(visit_action));
  preorder(n->right_child, std::move(visit_action));
}

template<class T>
void binary_tree<T>::postorder(node<T> *n, std::function<void(node<T> *)> &&visit_action) {
  if (n == nullptr) {
    return;
  }

  postorder(n->left_child, std::move(visit_action));
  postorder(n->right_child, std::move(visit_action));
  visit_action(n);
}

template<class T>
void binary_tree<T>::inorder(node<T> *n, std::function<void(node<T> *)> &&visit_action) {
  if (n == nullptr) {
    return;
  }

  inorder(n->left_child, std::move(visit_action));
  visit_action(n);
  inorder(n->right_child, std::move(visit_action));
}

template<class T>
long long binary_tree<T>::height() {
  return binary_tree<T>::height(this->root);
}

template<class T>
long long binary_tree<T>::height(node<T> *n) {
  if (n == nullptr) {
    return 0;
  }

  auto left_height = binary_tree<T>::height(n->left_child);
  auto right_height = binary_tree<T>::height(n->right_child);

  return std::max(left_height, right_height) + 1;
}

// Replaces 'current' node with 'other'
// This doesn't handle childrens' links which is the responsibility of the caller
template<typename T>
void binary_tree<T>::replace(node<T> *&current, node<T> *other) {
  auto ancestor = current->ancestor;
  switch (current->type) {
    case node_type::k_right_child:ancestor->right_child = other;
      break;

    case node_type::k_left_child:ancestor->left_child = other;
      break;

    case node_type::k_root:root = other;
      break;

    default:
      // Not handled for this type
      assert(false);
  }

  other->ancestor = ancestor;
  other->type = current->type;

  delete current;
  current = other;
}
}
}

namespace ds {
namespace bin_tree {
// Represents start and end of a segment
struct range {
  std::size_t lower_bound;
  std::size_t upper_bound;
};

// Response of a query call
template<class T>
struct response {
  bool is_valid;
  T data;
};

template<class T, class U>
struct seg_data {
  seg_data() : is_lazy(false) {}

  T data;
  bool is_lazy;
  U lazy_data;
};

template<class C, class T, class U>
class seg_tree : public binary_tree<seg_data<T, U>> {
 public:
  // container is a void pointer to the container
  // access_data - function pointer which returns the data from the container for the given index
  // merge_nodes - function pointer which performs the operation on 2 data points (min, max, sum etc.) and returns the result
  explicit seg_tree(C &container, std::size_t size,
                    T(*access_data)(C &, std::size_t),
                    T(*merge_nodes)(T, T),
                    T(*update_data)(range &segment, T &node_data, U &data));

  // Returns the result of the operation on the specified segment
  response<T> query(range &query_segment);

  // Updates the values in the specified segment
  void update_range(range &update_segment, U &data);
  void update_point(std::size_t idx, T &data);

  C container;
  std::size_t size;
  T (*merge_nodes)(T, T);
  T (*access_data)(C &, std::size_t);
  T (*update_data)(range &segment, T &node_data, U &data);

 private:
  node<seg_data<T, U>> *build_tree(node_type type, range segment);
  response<T> query(node<seg_data<T, U>> *n, range segment, range &query_segment);
  void update_range(node<seg_data<T, U>> *n, range &segment, range &update_segment, U &data);
  void propagate_laziness(node<seg_data<T, U>> *n, U &data);
  void update_point(node<seg_data<T, U>> *n, range &segment, std::size_t idx, U &data);

  static range left(range &segment) {
    return range{segment.lower_bound, (segment.lower_bound + segment.upper_bound) >> 1};
  }
  static range right(range &segment) {
    return range{((segment.lower_bound + segment.upper_bound) >> 1) + 1, segment.upper_bound};
  }
};

template<class C, class T, class U>
seg_tree<C, T, U>::seg_tree(C &container, std::size_t size,
                            T(*access_data)(C &, std::size_t),
                            T(*merge_nodes)(T, T),
                            T(*update_data)(range &segment, T &node_data, U &data)) :
    container(container), size(size), merge_nodes(merge_nodes), access_data(access_data), update_data(update_data) {
  range segment{0, size - 1};
  this->root = build_tree(node_type::k_root, segment);
}

template<class C, class T, class U>
response<T> seg_tree<C, T, U>::query(range &query_segment) {
  range segment{0, size - 1};
  return query(this->root, segment, query_segment);
}

template<class C, class T, class U>
void seg_tree<C, T, U>::update_range(range &update_segment, U &data) {
  range segment{0, size - 1};
  return update_range(this->root, segment, update_segment, data);
}

template<class C, class T, class U>
void seg_tree<C, T, U>::update_point(std::size_t idx, T &data) {
  range segment{0, size - 1};
  update_point(this->root, segment, idx, data);
}

template<class C, class T, class U>
node<seg_data<T, U>> *seg_tree<C, T, U>::build_tree(node_type type, range segment) {
  // Leaf node
  if (segment.lower_bound == segment.upper_bound) {
    // Store the c[i] value in the leaf node
    seg_data<T, U> node_data;
    node_data.data = access_data(container, segment.lower_bound);
    return new node<seg_data<T, U>>(node_data, type);
  }

  auto left_child = build_tree(node_type::k_left_child, left(segment));
  auto right_child = build_tree(node_type::k_right_child, right(segment));

  // Perform operation on the 2 nodes and store its result in the parent node
  seg_data<T, U> node_data;
  node_data.data = merge_nodes(left_child->data.data, right_child->data.data);
  auto *new_node = new node<seg_data<T, U>>(node_data, type);

  new_node->left_child = left_child;
  new_node->right_child = right_child;
  left_child->ancestor = right_child->ancestor = new_node;
  return new_node;
}

template<class C, class T, class U>
response<T> seg_tree<C, T, U>::query(node<seg_data<T, U>> *n, range segment, range &query_segment) {
  // Outside query range
  if (query_segment.lower_bound > segment.upper_bound || query_segment.upper_bound < segment.lower_bound) {
    return response<T>{false};
  }

  // Check if the current node is lazy
  if (n->data.is_lazy) {
    // Current node has some lazy data pending, update it first
    n->data.data = update_data(segment, n->data.data, n->data.lazy_data);

    // If the current node isn't a leaf node, then propagate laziness to its children
    propagate_laziness(n, n->data.lazy_data);

    // Get rid of the laziness!
    n->data.is_lazy = false;
  }

  // Completely within the query range
  if (segment.lower_bound >= query_segment.lower_bound && segment.upper_bound <= query_segment.upper_bound) {
    return response<T>{true, n->data.data};
  }

  auto left_response = query(n->left_child, left(segment), query_segment);
  auto right_response = query(n->right_child, right(segment), query_segment);

  if (!left_response.is_valid) {
    return right_response;
  }

  if (!right_response.is_valid) {
    return left_response;
  }

  return response<T>{true, merge_nodes(left_response.data, right_response.data)};
}

template<class C, class T, class U>
void seg_tree<C, T, U>::update_range(node<seg_data<T, U>> *n,
                                     range &segment,
                                     range &update_segment,
                                     U &data) {
  if (n->data.is_lazy) {
    // If the current node is lazy, need to update the node with the lazy value, if it exists
    n->data.data = update_data(segment, n->data.data, n->data.lazy_data);

    // If the current node isn't a leaf node, mark its children as lazy
    propagate_laziness(n, n->data.lazy_data);

    n->data.is_lazy = false;
  }

  // Completely outside query range
  if (update_segment.lower_bound > segment.upper_bound || update_segment.upper_bound < segment.lower_bound) {
    return;
  }

  // Completely within query range
  if (segment.lower_bound >= update_segment.lower_bound && segment.upper_bound <= update_segment.upper_bound) {
    n->data.data = update_data(segment, n->data.data, data);

    // If the current node isn't a leaf node, mark its children as lazy
    propagate_laziness(n, data);
    return;
  }

  update_range(n->left_child, left(segment), update_segment, data);
  update_range(n->right_child, right(segment), update_segment, data);

  n->data.data = merge_nodes(n->left_child->data.data, n->right_child->data.data);
}

// Induces/updates the laziness associated with the current node to its children
template<class C, class T, class U>
void seg_tree<C, T, U>::propagate_laziness(node<seg_data<T, U>> *n, U &data) {
  if (n->left_child == nullptr || n->right_child == nullptr) {
    return;
  }

  // Mark its  children as lazy, with the lazy data
  n->left_child->data.is_lazy = n->right_child->data.is_lazy = true;
  n->left_child->data.lazy_data = n->right_child->data.lazy_data = data;
}

template<class C, class T, class U>
void seg_tree<C, T, U>::update_point(node<seg_data<T, U>> *n, range &segment, std::size_t idx, U &data) {
  auto i = idx;
  auto j = idx;
  if (i > segment.upper_bound || j < segment.lower_bound) {
    return;
  }

  if (i == segment.lower_bound && j == segment.upper_bound) {
    n->data.data = update_data(segment, n->data.data, data);
    return;
  }

  update_point(n->left_child, left(segment), idx, data);
  update_point(n->right_child, right(segment), idx, data);

  n->data.data = merge_nodes(n->left_child->data.data, n->right_child->data.data);
}
}
}

template<class T>
T merge_nodes(T d1, T d2) {
  return d1 + d2;
}

template<class C, class T>
T access_data(C &container, std::size_t index) {
  return container[index];
}

template<class T, class U>
T update_data(ds::bin_tree::range &segment, T &node_data, U &data) {
  return data;
}

int main() {
  ui t, q;
  ul n, l, r;
  std::string line;
  std::vector<ul> numbers, sub_array_sums;

  std::cin >> t;
  for (ui c = 1; c <= t; ++c) {
    using namespace ds::bin_tree;

    numbers.clear();
    sub_array_sums.clear();
    std::cin >> n >> q;
    std::cin.ignore();

    std::getline(std::cin, line);
    std::istringstream tokenizer(line);
    while (tokenizer >> l) {
      numbers.emplace_back(l);
    }

    seg_tree<std::vector<ul>, ul, ul> num_tree(numbers, numbers.size(), access_data, merge_nodes, update_data);
    range query_segment{};

    for (ul i = 0; i < numbers.size(); ++i) {
      for (ul j = i; j < numbers.size(); ++j) {
        query_segment.lower_bound = i;
        query_segment.upper_bound = j;
        auto result = num_tree.query(query_segment);
        assert(result.is_valid);

        sub_array_sums.emplace_back(result.data);
      }
    }

    std::sort(sub_array_sums.begin(), sub_array_sums.end());

    seg_tree<std::vector<ul>, ul, ul>
        new_num_tree(sub_array_sums, sub_array_sums.size(), access_data, merge_nodes, update_data);

    printf("Case #%d:\n", c);
    while (q--) {
      std::cin >> l >> r;
      query_segment.lower_bound = l - 1;
      query_segment.upper_bound = r - 1;
      auto res = new_num_tree.query(query_segment);
      assert(res.is_valid);

      std::cout << res.data << std::endl;
    }
  }

  return 0;
}