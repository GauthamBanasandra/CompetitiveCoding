//
// Created by gauth on 14-05-2018.
//

#include <algorithm>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include <cassert>

using ll = long long;

enum class Colour {
    kWhite, kBlack
};

class Graph {
public:
    explicit Graph(std::size_t n_nodes, const std::vector<std::pair<int, int>> &edge_list);

    void ColourNodes();

private:
    std::vector<int> GetBlackNodes(const std::vector<std::pair<int, Colour>> &nodes);

    void ColourNode(std::size_t i_node, std::vector<std::pair<int, Colour>> &nodes, std::size_t n_black_nodes,
                    std::vector<int> &black_nodes);

    void PrintNodes(std::vector<int> &nodes) const;

    bool AreAllNeighboursWhite(int node, std::vector<std::pair<int, Colour>> &nodes);

    std::size_t n_nodes_;
    std::unordered_map<int, std::vector<int>> adj_list_;
    std::unordered_map<int, std::size_t> node_i_;
};

bool Graph::AreAllNeighboursWhite(int node, std::vector<std::pair<int, Colour>> &nodes) {
    for (const auto &neighbour : adj_list_[node]) {
        if (nodes[node_i_[neighbour]].second == Colour::kBlack) {
            return false;
        }
    }

    return true;
}

Graph::Graph(const std::size_t n_nodes, const std::vector<std::pair<int, int>> &edge_list) : n_nodes_(n_nodes) {
    for (std::size_t i = 1; i <= n_nodes_; ++i) {
        adj_list_[i];
        node_i_[i] = i - 1;
    }

    for (const auto &edge : edge_list) {
        adj_list_[edge.first].emplace_back(edge.second);
        adj_list_[edge.second].emplace_back(edge.first);
    }
}

void Graph::ColourNodes() {
    std::vector<std::pair<int, Colour>> nodes(node_i_.size());
    std::vector<int> black_nodes;

    for (const auto &node_i : node_i_) {
        nodes[node_i.second].first = node_i.first;
        nodes[node_i.second].second = Colour::kWhite;
    }

    ColourNode(0, nodes, 0, black_nodes);
    PrintNodes(black_nodes);
}

void Graph::PrintNodes(std::vector<int> &nodes) const {
    assert(!nodes.empty());

    std::sort(nodes.begin(), nodes.end());

    std::string nodes_str = std::to_string(nodes[0]);
    for (std::size_t i = 1; i < nodes.size(); ++i) {
        nodes_str += " " + std::to_string(nodes[i]);
    }

    std::cout << nodes.size() << std::endl;
    std::cout << nodes_str << std::endl;
}

std::vector<int> Graph::GetBlackNodes(const std::vector<std::pair<int, Colour>> &nodes) {
    std::vector<int> black_nodes;
    for (const auto &node : nodes) {
        if (node.second == Colour::kBlack) {
            black_nodes.emplace_back(node.first);
        }
    }

    return black_nodes;
}

void Graph::ColourNode(std::size_t i_node, std::vector<std::pair<int, Colour>> &nodes, std::size_t n_black_nodes,
                       std::vector<int> &black_nodes) {
    if (i_node >= n_nodes_) {
        if (n_black_nodes > black_nodes.size()) {
            black_nodes = GetBlackNodes(nodes);
        }

        return;
    }

    if (AreAllNeighboursWhite(nodes[i_node].first, nodes)) {
        nodes[i_node].second = Colour::kBlack;
        ColourNode(i_node + 1, nodes, n_black_nodes + 1, black_nodes);
    }

    nodes[i_node].second = Colour::kWhite;
    ColourNode(i_node + 1, nodes, n_black_nodes, black_nodes);
}

int main() {
    std::vector<std::pair<int, int>> edge_list;

    ll m, k;
    int p, q, n;

    std::cin >> m;
    while (m-- > 0) {
        edge_list.clear();
        std::cin >> n >> k;

        while (k-- > 0) {
            std::cin >> p >> q;
            edge_list.emplace_back(p, q);
        }

        Graph(n, edge_list).ColourNodes();
    }

    return 0;
}