#include <stdio.h>
#include <ios>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <cassert>

using color = long int;
using n_num = long int;

struct Node {
  n_num n;
  color c;
  Node *parent;
};

class Graph {
 public:
  long int k;
  std::unordered_map<n_num, n_num> kth_ancestor;
  std::unordered_map<n_num, Node> nodes;
  std::unordered_map<color, std::vector<n_num>> lineage_clr;
  std::unordered_map<n_num, std::unordered_set<Node *>> fwd_lnk, rev_lnk;

  explicit Graph(long int n, long int k);
  inline void DeclareParent(n_num p, n_num n);
  inline std::unordered_set<Node *> GetChildren(n_num n);
  void BuildSubtree(n_num p, n_num n);
};

Graph::Graph(long int n, long int k) {
  this->k = k;
  for (auto i = 1; i < n + 1; ++i) {
    nodes[i].n = i;
    scanf("%ld", &nodes[i].c);
  }

  long int x = 0, y = 0;
  for (auto i = 0; i < n - 1; ++i) {
    scanf("%ld%ld", &x, &y);
    fwd_lnk[x].insert(&nodes[y]);
    rev_lnk[y].insert(&nodes[x]);
  }
}

inline void Graph::DeclareParent(n_num p, n_num n) {
  fwd_lnk[n].erase(&nodes[p]);
  rev_lnk[n].erase(&nodes[p]);
}

inline std::unordered_set<Node *> Graph::GetChildren(n_num n) {
  std::unordered_set<Node *> children(fwd_lnk[n].begin(), fwd_lnk[n].end());
  children.insert(rev_lnk[n].begin(), rev_lnk[n].end());

  return children;
}

void Graph::BuildSubtree(n_num p, n_num n) {
  DeclareParent(p, n);
  auto &node = nodes[n];
  const auto find_lineage = lineage_clr.find(node.c);
  if (find_lineage != lineage_clr.end() && static_cast<n_num>(find_lineage->second.size()) >= k) {
    kth_ancestor[node.n] = find_lineage->second[static_cast<n_num>(find_lineage->second.size()) - k];
  } else {
    kth_ancestor[node.n] = -1;
  }

  lineage_clr[node.c].push_back(node.n);

  auto children = GetChildren(n);
  if (children.empty()) {
    return;
  }

  for (auto &child : children) {
    child->parent = &node;
    BuildSubtree(node.n, child->n);
  }
}

int main(int argc, char *argv[]) {
  std::ios::sync_with_stdio(false);

  long int n, k;
  scanf("%ld%ld", &n, &k);

  Graph g(n, k);
  g.BuildSubtree(0, 1);
  assert(g.nodes[1].parent == nullptr);

  for (n_num i = 1; i < n; ++i) {
    printf("%ld ", g.kth_ancestor[i]);
  }

  printf("%ld", g.kth_ancestor[n]);

  return 0;
}
