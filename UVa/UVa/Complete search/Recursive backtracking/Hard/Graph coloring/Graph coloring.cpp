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
    explicit Graph(const std::vector<std::pair<int, int>> &edge_list);

    void ColourNodes();

private:
    void InitializeNodeColours(std::unordered_map<int, Colour> &node_colour);

    void PrintColouredNodes(const std::unordered_map<int, Colour> &node_colour) const;

    void ColourNode(int node, std::unordered_map<int, Colour> &node_colour, std::unordered_set<int> &visited_nodes);

    bool AreAllNeighboursWhite(int node, std::unordered_map<int, Colour> &node_colour);

    std::unordered_map<int, std::vector<int>> adj_list_;
};

void Graph::ColourNode(int node, std::unordered_map<int, Colour> &node_colour, std::unordered_set<int> &visited_nodes) {
    /*if (visited_nodes.size() >= adj_list_.size()) {
        return;
    }*/

    if (AreAllNeighboursWhite(node, node_colour)) {
        node_colour[node] = Colour::kBlack;
    }

    for (const auto neighbour : adj_list_[node]) {
        if (visited_nodes.find(neighbour) != visited_nodes.end()) {
            continue;
        }

        visited_nodes.insert(neighbour);
        ColourNode(neighbour, node_colour, visited_nodes);
    }
}

bool Graph::AreAllNeighboursWhite(int node, std::unordered_map<int, Colour> &node_colour) {
    for (const auto &neighbour : adj_list_[node]) {
        if (node_colour[neighbour] == Colour::kBlack) {
            return false;
        }
    }

    return true;
}

Graph::Graph(const std::vector<std::pair<int, int>> &edge_list) {
    for (const auto &edge : edge_list) {
        adj_list_[edge.first].emplace_back(edge.second);
        adj_list_[edge.second].emplace_back(edge.first);
    }
}

void Graph::ColourNodes() {
    std::unordered_map<int, Colour> node_colour, max_node_colour;
    std::unordered_set<int> visited_nodes;

    auto count_black = [](std::pair<const int, Colour> &item) -> bool {
        return item.second == Colour::kBlack;
    };

    for (const auto &node : adj_list_) {
        InitializeNodeColours(node_colour);
        visited_nodes.clear();

        visited_nodes.insert(node.first);
        ColourNode(node.first, node_colour, visited_nodes);

        if (std::count_if(node_colour.begin(), node_colour.end(), count_black) >
            std::count_if(max_node_colour.begin(), max_node_colour.end(), count_black)) {
            max_node_colour = node_colour;
        }
    }

    PrintColouredNodes(max_node_colour);
}

void Graph::PrintColouredNodes(const std::unordered_map<int, Colour> &node_colour) const {
    std::vector<int> black_nodes;
    assert(!node_colour.empty());

    for (const auto &node : node_colour) {
        if (node.second == Colour::kBlack) {
            black_nodes.emplace_back(node.first);
        }
    }

    std::sort(black_nodes.begin(), black_nodes.end());

    std::string black_nodes_str = std::to_string(black_nodes[0]);
    for (std::size_t i = 1; i < black_nodes.size(); ++i) {
        black_nodes_str += " " + std::to_string(black_nodes[i]);
    }

    std::cout << black_nodes.size() << std::endl;
    std::cout << black_nodes_str << std::endl;
}

void Graph::InitializeNodeColours(std::unordered_map<int, Colour> &node_colour) {
    for (const auto &node : adj_list_) {
        node_colour[node.first] = Colour::kWhite;
    }
}

int main() {
    std::vector<std::pair<int, int>> edge_list{
            /*{1, 2},
            {1, 3},
            {2, 4},
            {2, 5},
            {3, 4},
            {3, 6},
            {4, 6},
            {5, 6}*/
    };

//    Graph(edge_list).ColourNodes();
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

        Graph(edge_list).ColourNodes();
    }

    return 0;
}