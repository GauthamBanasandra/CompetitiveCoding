//
// Created by gauth on 07-07-2018.
//

#include <iostream>
#include <vector>

using ll = long long;

struct Attraction {
    Attraction(int id, int popularity) : id(id), popularity(popularity), visits(0) {}

    bool operator<(const Attraction &other) const {
        return visits == other.visits ? popularity > other.popularity : visits < other.visits;
    }

    bool operator!=(const Attraction &other) const {
        return id != other.id;
    }

    bool operator==(const Attraction &other) const {
        return id == other.id;
    }

    int id;
    int popularity;
    ll visits;
};

void Print(int n, int k, ll v, const std::vector<Attraction> &attractions) {
    std::cout << "v : " << v << "\t: ";

    for (const auto attraction : attractions) {
        std::cout << attraction.id << " ";
    }

    std::cout << std::endl;
}