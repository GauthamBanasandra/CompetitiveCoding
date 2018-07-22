//
// Created by gauth on 07-07-2018.
//

#include <vector>
#include <string>
#include <algorithm>
#include <limits>
#include <iostream>
#include <cassert>

using ll = long long;

struct Attraction {
    Attraction(int id, int popularity) : id(id), popularity(popularity), visits(0) {}

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

void Print(int n, int k, ll v, const std::vector<Attraction> &attractions);

class Campus {
public:
    explicit Campus(int n);

    std::vector<Attraction> Visit(int k, ll v) const;

private:
    std::vector<Attraction> attractions_;

    int n_;
};

Campus::Campus(int n) : n_(n) {
    attractions_.reserve(static_cast<std::size_t>(n));

    for (int i = 0; i < n; ++i) {
        attractions_.emplace_back(i, n - i);
    }
}

std::vector<Attraction> Campus::Visit(int k, ll v) const {
    auto attractions(attractions_);

    for (ll i = 0; i < v % n_; ++i) {
        for (int j = 0; j < k; ++j) {
            ++attractions[j].visits;
        }

        std::sort(attractions.begin(), attractions.end(),
                  [](const Attraction &a1, const Attraction &a2) -> bool {
                      return a1.visits == a2.visits ? a1.popularity > a2.popularity : a1.visits < a2.visits;
                  });
    }

    std::sort(attractions.begin(), attractions.begin() + k,
              [](const Attraction &a1, const Attraction &a2) -> bool {
                  return a1.popularity > a2.popularity;
              });

    return std::vector<Attraction>(attractions.begin(), attractions.begin() + k);
}

int main() {
    int t, k, n;
    ll v;
    std::vector<std::string> attraction_names;

    std::cin >> t;
    for (int i = 1; i <= t; ++i) {
        attraction_names.clear();
        std::cin >> n >> k >> v;

        attraction_names.resize(n);
        for (int j = 0; j < n; ++j) {
            std::cin >> attraction_names[j];
        }

        std::cout << "Case #" << i << ": ";
        std::string attractions_visit;
        for (const auto attraction : Campus(n).Visit(k, v - 1)) {
            attractions_visit += attraction_names[attraction.id] + " ";
        }

        attractions_visit.pop_back();
        std::cout << attractions_visit << std::endl;
    }

    return 0;
}