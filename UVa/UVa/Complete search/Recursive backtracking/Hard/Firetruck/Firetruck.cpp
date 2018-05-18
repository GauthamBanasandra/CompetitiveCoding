//
// Created by gauth on 18-05-2018.
//

#include <algorithm>
#include <vector>
#include <list>
#include <string>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include <limits>
#include <cassert>

void PrintCostMap(const std::vector<std::vector<int>> &cost_map);

const auto infinity = std::numeric_limits<int>::max();

struct Tracker {
public:
    void Visit(int corner) { tracker_.insert(corner); }

    void UndoVisit(int corner);

    bool IsVisited(int corner) { return tracker_.find(corner) != tracker_.end(); }

private:
    std::unordered_set<int> tracker_;
};

void Tracker::UndoVisit(int corner) {
    assert(IsVisited(corner));

    tracker_.erase(corner);
}

class City {
public:
    City(int destination, const std::list<std::pair<int, int>> &adj_corners);

    bool PathExists(int from, int to);

    void PrintAllRoutes();

private:
    void NextRoute(int corner, std::list<int> &route, Tracker &tracker, std::list<std::list<int>> &routes);

    void PrintRoutes(const std::list<std::list<int>> &routes);

    void InitializeCostMap(std::size_t max_corner);

    int destination_;
    std::vector<std::vector<int>> cost_map_;
    std::unordered_map<int, std::list<int>> city_map_;
};

void City::NextRoute(int corner, std::list<int> &route, Tracker &tracker, std::list<std::list<int>> &routes) {
    if (corner == destination_) {
        routes.emplace_back(route);
        return;
    }

    for (const auto adj_corner : city_map_[corner]) {
        if (tracker.IsVisited(adj_corner)) {
            continue;
        }

        route.emplace_back(adj_corner);
        tracker.Visit(adj_corner);

        NextRoute(adj_corner, route, tracker, routes);

        tracker.UndoVisit(adj_corner);
        route.pop_back();
    }
}

City::City(int destination, const std::list<std::pair<int, int>> &adj_corners) : destination_(destination) {
    auto max_corner = static_cast<std::size_t>(destination);
    for (const auto corner : adj_corners) {
        city_map_[corner.first].emplace_back(corner.second);
        city_map_[corner.second].emplace_back(corner.first);

        max_corner = std::max(max_corner, static_cast<std::size_t>(std::max(corner.first, corner.second)));
    }

    InitializeCostMap(max_corner);
}

void City::InitializeCostMap(std::size_t max_corner) {
    std::vector<int> row(max_corner, infinity);
    cost_map_.reserve(max_corner);
    for (std::size_t i = 0; i < max_corner; ++i) {
        cost_map_.emplace_back(row);
    }

    for (const auto &corner : city_map_) {
        for (const auto neighbour : corner.second) {
            cost_map_[corner.first - 1][neighbour - 1] = 1;
        }
    }

    for (std::size_t k = 0; k < max_corner; ++k) {
        for (std::size_t i = 0; i < max_corner; ++i) {
            for (std::size_t j = 0; j < max_corner; ++j) {
                cost_map_[i][j] = i == j ? 0 : std::min(cost_map_[i][j],
                                                        (cost_map_[i][k] == infinity || cost_map_[k][j] == infinity
                                                         ? infinity : cost_map_[i][k] + cost_map_[k][j]));
            }
        }
    }
}

void City::PrintAllRoutes() {
    std::list<std::list<int>> routes;

    if (PathExists(1, destination_)) {
        std::list<int> route;
        Tracker tracker;

        route.emplace_back(1);
        tracker.Visit(1);
        NextRoute(1, route, tracker, routes);
    }

    routes.sort();
    PrintRoutes(routes);
}

void City::PrintRoutes(const std::list<std::list<int>> &routes) {
    std::string output;
    for (const auto &route : routes) {
        std::string corner_str;
        for (const auto corner : route) {
            corner_str += std::to_string(corner) + " ";
        }

        if (!corner_str.empty()) {
            corner_str.pop_back();
        }

        output += corner_str + "\n";
    }

    std::cout << output;
    printf("There are %lu routes from the firestation to streetcorner %d.\n", routes.size(), destination_);
}

bool City::PathExists(int from, int to) {
    assert(from > 0 && to > 0);
    --from;
    --to;
    return cost_map_[from][to] != infinity;
}

int main() {
    int destination, c1, c2;
    long long t = 0;
    std::string line;
    std::list<std::pair<int, int>> adj_corners;

    while (std::getline(std::cin, line), !std::cin.eof()) {
        std::istringstream tokenizer(line);
        tokenizer >> destination;
        adj_corners.clear();

        while (std::cin >> c1 >> c2, c1 || c2) {
            adj_corners.emplace_back(c1, c2);
        }

        printf("CASE %lld:\n", ++t);
        City(destination, adj_corners).PrintAllRoutes();
        std::cin.ignore();
    }

    return 0;
}