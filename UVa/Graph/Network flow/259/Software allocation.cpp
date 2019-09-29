// WIP

#include <algorithm>
#include <cassert>
#include <iostream>
#include <limits>
#include <ostream>
#include <queue>
#include <sstream>
#include <string>
#include <tuple>
#include <unordered_map>
#include <utility>
#include <vector>

using Node = size_t;
using Capacity = int;
using Application = char;
using Computer = char;

const auto infinity = std::numeric_limits<Capacity>::max();
const auto unvisited = -1;

class FlowNetwork {
public:
  explicit FlowNetwork(
      const std::vector<std::tuple<Application, int, std::vector<Computer>>>
          &job_descriptions);

  Capacity GetAllocations();

private:
  Capacity Augment(const std::vector<Node> &parent);
  std::pair<bool, std::vector<Node>> FindAugmentingPath();

  const size_t num_nodes_;
  const Node source_{0};
  const Node sink_;
  std::unordered_map<Node, Application> id_app_;
  std::vector<std::unordered_map<Node, Capacity>> adj_list_;
};

FlowNetwork::FlowNetwork(
    const std::vector<std::tuple<Application, int, std::vector<Computer>>>
        &job_descriptions)
    : num_nodes_{10 + 2 + job_descriptions.size()},
      sink_{10 + 1 + job_descriptions.size()} {
  adj_list_.resize(num_nodes_);

  Node id = 1;
  std::unordered_map<Application, Node> app_id;
  for (const auto &[app, num_requests, computers] : job_descriptions) {
    if (app_id.find(app) == app_id.end()) {
      id_app_[id] = app;
      app_id[app] = id++;
    }
    auto application_id = app_id[app];
    for (const auto &computer : computers) {
      auto computer_id = job_descriptions.size() + computer - '0' + 1;
      adj_list_[application_id][computer_id] = infinity;
      adj_list_[computer_id][application_id] = 0;
    }
    adj_list_[source_][application_id] = num_requests;
    adj_list_[application_id][source_] = 0;
  }
  for (auto computer_id = job_descriptions.size() + 1; computer_id < sink_;
       ++computer_id) {
    adj_list_[computer_id][sink_] = 1;
    adj_list_[sink_][computer_id] = 0;
  }
}

Capacity FlowNetwork::GetAllocations() {
  auto max_flow = 0, flow = 0;
  do {
    auto [is_reachable, bfs_spanning_tree] = FindAugmentingPath();
    if (!is_reachable) {
      return max_flow;
    }
    flow = Augment(bfs_spanning_tree);
    max_flow += flow;
  } while (flow != 0);
  return max_flow;
}

Capacity FlowNetwork::Augment(const std::vector<Node> &parent) {
  auto min_capacity = infinity;
  for (auto node = sink_; node != source_; node = parent[node]) {
    min_capacity = std::min(min_capacity, adj_list_[parent[node]][node]);
  }
  for (auto node = sink_; node != source_; node = parent[node]) {
    adj_list_[parent[node]][node] -= min_capacity;
    adj_list_[node][parent[node]] += min_capacity;
  }
  return min_capacity;
}

std::pair<bool, std::vector<Node>> FlowNetwork::FindAugmentingPath() {
  std::vector<int> visited(num_nodes_, unvisited);
  std::vector<Node> parent(num_nodes_, std::numeric_limits<Node>::max());
  std::queue<Node> order;
  visited[source_] = 1;
  order.emplace(source_);

  while (!order.empty()) {
    const auto node = order.front();
    order.pop();
    if (node == sink_) {
      return std::make_pair(true, std::move(parent));
    }

    for (const auto &[adj_node, capacity] : adj_list_[node]) {
      if (capacity > 0 && visited[adj_node] == unvisited) {
        parent[adj_node] = node;
        visited[adj_node] = 1;
        order.emplace(adj_node);
      }
    }
  }
  return std::make_pair(false, std::move(parent));
}

int main(int argc, char *argv[]) {
  std::string line;
  int num_requests;
  Application app;
  Computer computer;

  while (std::getline(std::cin, line), !std::cin.eof()) {
    std::vector<std::tuple<Application, int, std::vector<Computer>>>
        job_descriptions;
    while (!line.empty()) {
      std::istringstream tokenizer(line);
      tokenizer >> app >> num_requests;
      std::vector<Computer> computers;
      while (tokenizer >> computer, computer != ';') {
        computers.emplace_back(computer);
      }
      job_descriptions.emplace_back(app, num_requests, computers);
      std::getline(std::cin, line);
    }
    std::cout << FlowNetwork(job_descriptions).GetAllocations() << std::endl;
  }
  return 0;
}
