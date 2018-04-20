#include <memory>
#include <cassert>
#include <functional>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

void print(const std::vector<int> &data);

void print(const std::unordered_map<int, int> &kv);

using frequency = std::unordered_map<int, int>;

namespace ds {
    namespace bin_tree {
        enum class node_type {
            k_left_child, k_right_child, k_root
        };

        template<typename T>
        class node {
        public:
            explicit node(const T &data, const node_type type) : type(type), ancestor(nullptr), left_child(nullptr),
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
                case node_type::k_left_child:
                    ancestor->left_child = nullptr;
                    break;

                case node_type::k_right_child:
                    ancestor->right_child = nullptr;
                    break;

                case node_type::k_root:
                    break;

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

            void inorder(std::function<void(node<T> *n)> visit_action = [](node<T> *n) -> void {
                std::cout << n->data << '\n';
            });

            // C++ doesn't allow a member to be used as the default value (for node as root)
            // Thus, we need expose traversal methods as wrappers of these functions
            void preorder(node<T> *n, std::function<void(node<T> *)> &&visit_action);

            void postorder(node<T> *n, std::function<void(node<T> *)> &&visit_action);

            void inorder(node<T> *n, std::function<void(node<T> *)> &&visit_action);

            long long height();

            static long long height(const node<T> *n);

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
        long long binary_tree<T>::height(const node<T> *n) {
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
                case node_type::k_right_child:
                    ancestor->right_child = other;
                    break;

                case node_type::k_left_child:
                    ancestor->left_child = other;
                    break;

                case node_type::k_root:
                    root = other;
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

        // Specifies the kind of update that must be done
        // Memoryless - Updates the container
        // Memory - Calls merge_node with the value provided with the node's value
        enum class update_mode {
            k_memory, k_memoryless
        };

        template<class C, class T>
        class seg_tree : public binary_tree<T> {
        public:
            // container is a void pointer to the container
            // access_data - function pointer which returns the data from the container for the given index
            // merge_nodes - function pointer which performs the operation on 2 data points (min, max, sum etc.) and returns the result
            explicit seg_tree(const C &container, std::size_t size, T(*access_data)(const C &, std::size_t),
                              T(*merge_nodes)(T, T));

            // Returns the result of the operation on the specified segment
            response<T> query(const range &query_segment);

            // Updates the values in the specified segment
            void update_range(const range &update_segment, const char data, const update_mode mode);

            C container;
            std::size_t size;

            T (*merge_nodes)(T, T);

            T (*access_data)(const C &, std::size_t);

        private:
            node<T> *build_tree(node_type type, const range &segment) const;

            response<T> query(node<T> *n, const range &segment, const range &query_segment);

            void update_node(node<T> *n, const char data, const update_mode mode);

            void update_range(node<T> *n, const range &segment, const range &update_segment, const char data,
                              const update_mode mode);

            void propagate_laziness(node<T> *n, char data);

            // Stores the data which will needs to get updated in the next query/update in each node
            std::unordered_map<node<T> *, T> lazy_store_;
        };

        template<class C, class T>
        seg_tree<C, T>::seg_tree(const C &container, const std::size_t size,
                                 T(*access_data)(const C &, const std::size_t), T(*merge_nodes)(T, T)) : container(
                container), size(size), merge_nodes(merge_nodes), access_data(access_data) {
            const range segment{0, size - 1};
            this->root = build_tree(node_type::k_root, segment);
        }

        template<class C, class T>
        response<T> seg_tree<C, T>::query(const range &query_segment) {
            const range segment{0, size - 1};
            return query(this->root, segment, query_segment);
        }

        template<class C, class T>
        void seg_tree<C, T>::update_range(const range &update_segment, const char data, const update_mode mode) {
            const range segment{0, size - 1};
            return update_range(this->root, segment, update_segment, data, mode);
        }

        template<class C, class T>
        node<T> *seg_tree<C, T>::build_tree(const node_type type, const range &segment) const {
            // Leaf node
            if (segment.lower_bound == segment.upper_bound) {
                // Store the c[i] value in the leaf node
                return new node<T>(access_data(container, segment.lower_bound), type);
            }

            range new_segment;

            // Recurse left
            new_segment.lower_bound = segment.lower_bound;
            new_segment.upper_bound = (segment.lower_bound + segment.upper_bound) >> 1;
            const auto left_child = build_tree(node_type::k_left_child, new_segment);

            // Recurse right
            new_segment.lower_bound = new_segment.upper_bound + 1;
            new_segment.upper_bound = segment.upper_bound;
            const auto right_child = build_tree(node_type::k_right_child, new_segment);

            // Perform operation on the 2 nodes and store its result in the parent node
            const auto new_node = new node<T>(merge_nodes(left_child->data, right_child->data), type);
            new_node->left_child = left_child;
            new_node->right_child = right_child;
            left_child->ancestor = right_child->ancestor = new_node;
            return new_node;
        }


        template<class C, class T>
        response<T> seg_tree<C, T>::query(node<T> *n, const range &segment, const range &query_segment) {
            // Outside query range
            if (query_segment.lower_bound > segment.upper_bound || query_segment.upper_bound < segment.lower_bound) {
                return response<T>{false};
            }

            // Check if the current node is lazy
            auto find = lazy_store_.find(n);
            if (find != lazy_store_.end()) {
                // Current node has some lazy data pending, update it first
                n->data = merge_nodes(n->data, find->second);

                // If the current node isn't a leaf node, then propagate laziness to its children
                propagate_laziness(n, find->second);

                // Get rid of the laziness!
                lazy_store_.erase(find);
            }

            // Completely within the query range
            if (segment.lower_bound >= query_segment.lower_bound && segment.upper_bound <= query_segment.upper_bound) {
                return response<T>{true, n->data};
            }

            range new_segment;

            new_segment.lower_bound = segment.lower_bound;
            new_segment.upper_bound = (segment.lower_bound + segment.upper_bound) >> 1;
            const auto left_response = query(n->left_child, new_segment, query_segment);

            new_segment.lower_bound = new_segment.upper_bound + 1;
            new_segment.upper_bound = segment.upper_bound;
            const auto right_response = query(n->right_child, new_segment, query_segment);

            if (!left_response.is_valid) {
                return right_response;
            }

            if (!right_response.is_valid) {
                return left_response;
            }

            return response<T>{true, merge_nodes(left_response.data, right_response.data)};
        }

        // Update the node's data with the one provided according to the mode
        template<class C, class T>
        void seg_tree<C, T>::update_node(node<T> *n, const char data, const update_mode mode) {
            switch (mode) {
                case update_mode::k_memory:
                    n->data = merge_nodes(n->data, data);
                    break;

                case update_mode::k_memoryless:
                    n->data = data;
                    break;

                default:
                    // Unhandled for this update_mode
                    assert(false);
            }
        }

        template<class C, class T>
        void
        seg_tree<C, T>::update_range(node<T> *n, const range &segment, const range &update_segment, const char data,
                                     const update_mode mode) {
            auto find = lazy_store_.find(n);
            if (find != lazy_store_.end()) {
                // If the current node is lazy, need to update the node with the lazy value, if it exists
                update_node(n, find->second, mode);

                // If the current node isn't a leaf node, mark its children as lazy
                propagate_laziness(n, find->second);

                lazy_store_.erase(find);
            }

            // Completely outside query range
            if (update_segment.lower_bound > segment.upper_bound || update_segment.upper_bound < segment.lower_bound) {
                return;
            }

            // Completely within query range
            if (segment.lower_bound >= update_segment.lower_bound &&
                segment.upper_bound <= update_segment.upper_bound) {
                update_node(n, data, mode);

                // If the current node isn't a leaf node, mark its children as lazy
                propagate_laziness(n, data);
                return;
            }

            range new_segment;
            new_segment.lower_bound = segment.lower_bound;
            new_segment.upper_bound = (segment.lower_bound + segment.upper_bound) >> 1;
            update_range(n->left_child, new_segment, update_segment, data, mode);

            new_segment.lower_bound = new_segment.upper_bound + 1;
            new_segment.upper_bound = segment.upper_bound;
            update_range(n->right_child, new_segment, update_segment, data, mode);

            n->data = merge_nodes(n->left_child->data, n->right_child->data);
        }

        // Induces/updates the laziness associated with the current node to its children
        template<class C, class T>
        void seg_tree<C, T>::propagate_laziness(node<T> *n, char data) {
            // TODO : Verify this - outcome is that it's a leaf node. Change || to &&
            if (n->left_child != nullptr || n->right_child != nullptr) {
                return;
            }

            // Mark its  children as lazy, with the lazy data
            auto left_find = lazy_store_.find(n->left_child);
            if (left_find != lazy_store_.end()) {
                left_find->second = merge_nodes(left_find->second, data);
            } else {
                lazy_store_[n->left_child] = data;
            }

            auto right_find = lazy_store_.find(n->right_child);
            if (right_find != lazy_store_.end()) {
                right_find->second = merge_nodes(right_find->second, data);
            } else {
                lazy_store_[n->right_child] = data;
            }
        }
    }
}

template<class T>
T merge_nodes(T d1, T d2) {
    return std::max(d1, d2);
}

template<class C, class T>
T access_data(const C &container, std::size_t index) {
    return container[index];
}

int main(int argc, char *argv[]) {
    int n, q;
    std::string line;
    std::vector<int> data, t_data, t_res;
    std::unordered_map<int, int> f;
    std::unordered_map<int, std::pair<int, int>> p;

    while (std::cin >> n, n) {
        data.clear();
        t_data.clear();
        f.clear();
        p.clear();
        data.resize(n);
        t_data.resize(n);
        std::cin >> q;
        std::cin.ignore();
        std::getline(std::cin, line);

        std::istringstream tokens(line);
        for (auto i = 0; i < n; ++i) {
            tokens >> data[i];
            ++f[data[i]];

            auto find = p.find(data[i]);
            if (find == p.end()) {
                p[data[i]] = std::make_pair(i, i);
            } else {
                ++find->second.second;
            }
        }

        for (const auto &kv : p) {
            for (auto i = kv.second.first; i <= kv.second.second; ++i) {
                t_data[i] = f[kv.first];
            }
        }
        ds::bin_tree::seg_tree<std::vector<int>, int> seg_tree(t_data, t_data.size(), access_data, merge_nodes);
        ds::bin_tree::range s;
        while (q--) {
            auto x = 0, y = 0;
            std::cin >> x >> y;
            --x;
            --y;

            t_res.clear();
            if (data[x] == data[y]) {
                std::cout << y - x + 1 << std::endl;
                continue;
            }

            if (x == p[data[x]].first) {
                s.lower_bound = x;
            } else {
                s.lower_bound = p[data[x]].second + 1;
                t_res.push_back(p[data[x]].second - x + 1);
            }

            if (y == p[data[y]].second) {
                s.upper_bound = y;
            } else {
                assert(p[data[y]].first > 0);

                s.upper_bound = p[data[y]].first - 1;
                t_res.push_back(y - p[data[y]].first + 1);
            }

            if (s.lower_bound < s.upper_bound) {
                const auto res = seg_tree.query(s);
                t_res.push_back(res.data);
            }

            std::cout << *std::max_element(t_res.begin(), t_res.end()) << std::endl;
        }
    }

    return 0;
}
