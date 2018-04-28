//
// Created by gauth on 28-04-2018.
//

#include <vector>
#include <cstdlib>
#include <string>
#include <sstream>
#include <unordered_set>
#include <map>
#include <iostream>
#include <cassert>

using AdjacencyList = std::map<int, std::vector<int>>;
using EdgeList = std::vector<std::pair<int, int>>;

struct Tracker {
public:
    Tracker(size_t n_nodes_, int first_node) : n_nodes_(n_nodes_) {
        Visit(first_node);
    }

    bool IsVisited(int node) const { return visited_nodes_.find(node) != visited_nodes_.end(); }

    bool IsHamiltonianCycle() const;

    bool IsHamiltonianCycle(int node) const;

    void Visit(int node);

    void UndoVisit(int node);

    std::vector<int> walk;

private:
    std::size_t n_nodes_;
    std::unordered_set<int> visited_nodes_;
};

bool Tracker::IsHamiltonianCycle() const {
    assert(!walk.empty());

    return (visited_nodes_.size() == n_nodes_) && (walk[0] == walk[walk.size() - 1]);
}

bool Tracker::IsHamiltonianCycle(int node) const {
    assert(!walk.empty());

    return (walk[0] == node) && (visited_nodes_.size() == n_nodes_);
}

void Tracker::Visit(int node) {
    visited_nodes_.insert(node);
    walk.emplace_back(node);
}

void Tracker::UndoVisit(int node) {
    visited_nodes_.erase(node);

    assert(walk.back() == node);

    walk.pop_back();
}

class Graph {
public:
    explicit Graph(const EdgeList &edge_list);

    void PrintHamiltonianCycle();

private:
    bool Visit(int node, Tracker &tracker);

    AdjacencyList adjacency_list_;
};

bool Graph::Visit(int node, Tracker &tracker) {
    if (tracker.IsHamiltonianCycle()) {
        return true;
    }

    for (const auto adjacent_node : adjacency_list_[node]) {
        if (!tracker.IsVisited(adjacent_node) || tracker.IsHamiltonianCycle(adjacent_node)) {
            tracker.Visit(adjacent_node);
            if (Visit(adjacent_node, tracker)) {
                return true;
            }

            tracker.UndoVisit(adjacent_node);
        }
    }

    return false;
}

void Graph::PrintHamiltonianCycle() {
    for (const auto &kv : adjacency_list_) {
        Tracker tracker(adjacency_list_.size(), kv.first);
        if (Visit(kv.first, tracker)) {
            std::cout << tracker.walk[0];
            for (int i = 1; i < tracker.walk.size(); ++i) {
                std::cout << " " << tracker.walk[i];
            }

            std::cout << std::endl;
            return;
        }
    }

    printf("N\n");
}

Graph::Graph(const EdgeList &edge_list) {
    for (const auto &edge : edge_list) {
        adjacency_list_[edge.first].emplace_back(edge.second);
        adjacency_list_[edge.second].emplace_back(edge.first);
    }
}

int main() {
    int u, v;
    std::string line;
    EdgeList edge_list;

    while (std::getline(std::cin, line), !std::cin.eof()) {
        edge_list.clear();
        while (std::getline(std::cin, line), line[0] != '%') {
            std::istringstream tokenizer(line);
            tokenizer >> u >> v;
            edge_list.emplace_back(u, v);
        }

        Graph(edge_list).PrintHamiltonianCycle();
    }

    return 0;
}