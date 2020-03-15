#include <algorithm>
#include <cassert>
#include <ios>
#include <iostream>
#include <limits>
#include <memory>
#include <numeric>
#include <ostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

namespace uva_115 {
using NodeID = size_t;
using Relation = std::unordered_map<NodeID, int>;

const auto infinity = std::numeric_limits<NodeID>::max();

class RelationFinder {
public:
  RelationFinder(
      const std::unordered_set<std::string> &nodes_names,
      const std::vector<std::pair<std::string, std::string>> &edge_list_names);

  std::string Find(const std::string &p, const std::string &q);

private:
  void FindRoots();
  std::unique_ptr<Relation> FindRelation(NodeID node, NodeID node1,
                                         NodeID node2);
  std::string GetRelationDescription(const std::unique_ptr<Relation> &relation,
                                     const NodeID &node1,
                                     const NodeID &node2) const;
  static std::string Concatenate(const std::vector<std::string> &words,
                                 const std::string &delimiter = " ");
  static void MergeRelations(std::unique_ptr<Relation> &target,
                             std::unique_ptr<Relation> &source);

  std::vector<std::vector<NodeID>> adj_list_;
  std::vector<NodeID> parent_;
  std::unordered_set<NodeID> roots_;
  std::unordered_map<std::string, NodeID> node_name_id_;
};

RelationFinder::RelationFinder(
    const std::unordered_set<std::string> &nodes_names,
    const std::vector<std::pair<std::string, std::string>> &edge_list_names) {
  NodeID id{0};
  for (const auto &node_name : nodes_names) {
    node_name_id_[node_name] = id++;
  }

  const auto num_nodes = node_name_id_.size();
  adj_list_.resize(num_nodes);
  parent_.resize(num_nodes);
  std::iota(parent_.begin(), parent_.end(), 0);

  for (const auto &[u_name, v_name] : edge_list_names) {
    const auto u = node_name_id_.at(u_name);
    const auto v = node_name_id_.at(v_name);

    adj_list_[v].emplace_back(u);
    parent_[u] = v;
  }

  FindRoots();
}

std::string RelationFinder::Find(const std::string &p, const std::string &q) {
  auto find_it = node_name_id_.find(p);
  if (find_it == node_name_id_.end()) {
    return "no relation";
  }
  const auto node1 = find_it->second;
  find_it = node_name_id_.find(q);
  if (find_it == node_name_id_.end()) {
    return "no relation";
  }
  const auto node2 = find_it->second;

  for (const auto &root : roots_) {
    auto relation = FindRelation(root, node1, node2);
    if (relation != nullptr && relation->size() == 2) {
      return GetRelationDescription(relation, node1, node2);
    }
  }
  return "no relation";
}

void RelationFinder::FindRoots() {
  const auto num_nodes = node_name_id_.size();

  std::vector<bool> memo(num_nodes);
  auto find_root = [this, &memo](NodeID root) -> NodeID {
    while (parent_[root] != root) {
      if (memo[root]) {
        return infinity;
      }
      root = parent_[root];
      memo[root] = true;
    }
    return root;
  };

  for (NodeID id{0}; id < num_nodes; ++id) {
    auto root = find_root(id);
    if (root != infinity) {
      roots_.insert(root);
    }
  }
}

std::unique_ptr<Relation> RelationFinder::FindRelation(const NodeID node,
                                                       const NodeID node1,
                                                       const NodeID node2) {
  std::unique_ptr<Relation> relation;
  if (node == node1 || node == node2) {
    relation = std::make_unique<Relation>();
    (*relation)[node] = -1;
  }

  for (const auto &child : adj_list_[node]) {
    auto child_rel = FindRelation(child, node1, node2);
    MergeRelations(relation, child_rel);

    if (relation != nullptr && relation->size() == 2) {
      return relation;
    }
  }

  if (relation != nullptr && relation->size() == 1) {
    ++relation->begin()->second;
  }
  return relation;
}

std::string RelationFinder::GetRelationDescription(
    const std::unique_ptr<Relation> &relation, const NodeID &node1,
    const NodeID &node2) const {
  const auto k1 = relation->at(node1);
  const auto k2 = relation->at(node2);

  std::vector<std::string> desc_words;
  auto add_prefix = [&desc_words](const int k) {
    for (auto i = 0; i < k; ++i) {
      desc_words.emplace_back("great");
    }
    if (!desc_words.empty()) {
      desc_words.back() = "grand";
    }
  };

  if (k1 == -1) {
    add_prefix(k2);
    desc_words.emplace_back("parent");
    return Concatenate(desc_words);
  }
  if (k2 == -1) {
    add_prefix(k1);
    desc_words.emplace_back("child");
    return Concatenate(desc_words);
  }
  if (k1 == 0 && k2 == 0) {
    return "sibling";
  }

  desc_words.emplace_back(std::to_string(std::min(k1, k2)));
  desc_words.emplace_back("cousin");
  const auto j = std::abs(k1 - k2);
  if (j == 0) {
    return Concatenate(desc_words);
  }
  desc_words.emplace_back("removed");
  desc_words.emplace_back(std::to_string(j));
  return Concatenate(desc_words);
}

std::string RelationFinder::Concatenate(const std::vector<std::string> &words,
                                        const std::string &delimiter) {
  std::stringstream result;
  std::string separator;

  for (const auto &word : words) {
    result << separator << word;
    separator = delimiter;
  }
  return result.str();
}

void RelationFinder::MergeRelations(std::unique_ptr<Relation> &target,
                                    std::unique_ptr<Relation> &source) {
  if (source == nullptr) {
    return;
  }
  if (target == nullptr) {
    target = std::move(source);
    return;
  }
  // This is possible only for C++17 and above
  // Seems like UVa doesn't have it and hence coding it manually
  // target->merge(*source);

  for (const auto &key_value : *source) {
    target->emplace(key_value);
  }
  source->clear();

  assert(source->empty());
}
} // namespace uva_115

int main(int argc, char *argv[]) {
  std::ios::sync_with_stdio(false);

  std::string person1;
  std::string person2;
  std::unordered_set<std::string> people;
  std::vector<std::pair<std::string, std::string>> edge_list;

  while (std::cin >> person1 >> person2, person1 != "no.child") {
    people.insert(person1);
    people.insert(person2);
    edge_list.emplace_back(person1, person2);
  }

  uva_115::RelationFinder rel_finder(people, edge_list);
  while (std::cin >> person1 >> person2, !std::cin.eof()) {
    std::cout << rel_finder.Find(person1, person2) << std::endl;
  }

  return 0;
}
