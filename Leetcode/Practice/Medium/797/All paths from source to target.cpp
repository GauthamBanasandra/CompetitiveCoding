#include <iostream>
#include <vector>

using namespace std;

using Node = int;

class Solution {
public:
  vector<vector<int>> allPathsSourceTarget(vector<vector<int>> &graph);

private:
  void Dfs(Node u, const vector<vector<int>> &graph, vector<int> &path);
  void InitializeDegrees(const vector<vector<int>> &graph);

  vector<vector<Node>> all_paths_;
  vector<int> in_degree_;
  vector<int> out_degree_;
};

vector<vector<int>> Solution::allPathsSourceTarget(vector<vector<int>> &graph) {
  InitializeDegrees(graph);

  vector<Node> path;
  Dfs(0, graph, path);

  return all_paths_;
}

void Solution::Dfs(Node u, const vector<vector<int>> &graph,
                   vector<int> &path) {
  if (u == static_cast<Node>(graph.size()) - 1) {
    path.emplace_back(u);
    all_paths_.emplace_back(path);
    path.pop_back();
    return;
  }

  path.emplace_back(u);

  for (const Node v : graph[u]) {
    Dfs(v, graph, path);
  }

  path.pop_back();
}

void Solution::InitializeDegrees(const vector<vector<int>> &graph) {
  in_degree_.resize(graph.size());
  out_degree_.resize(graph.size());
  for (auto u = 0; u < static_cast<Node>(graph.size()); ++u) {
    for (const Node v : graph[u]) {
      ++in_degree_[v];
      ++out_degree_[u];
    }
  }
}

int main(int argc, char *argv[]) {
  vector<vector<Node>> graph{{4, 3, 1}, {3, 2, 4}, {3}, {4}, {}};

  for (const auto &path : Solution().allPathsSourceTarget(graph)) {
    for (const auto node : path) {
      cout << node << ", ";
    }
    cout << endl;
  }

  return 0;
}
