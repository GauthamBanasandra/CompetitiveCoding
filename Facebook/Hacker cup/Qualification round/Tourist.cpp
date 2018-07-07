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

    void Visit(int k, ll v) const;

private:
    bool IsSame(const std::vector<Attraction> &attractions) const;

    std::vector<Attraction> attractions_;

    int n_;
};

Campus::Campus(int n) : n_(n) {
    attractions_.reserve(static_cast<std::size_t>(n));

    for (int i = 0; i < n; ++i) {
        attractions_.emplace_back(i, n - i);
    }
}

void Campus::Visit(int k, ll v) const {
    auto attractions(attractions_);
    std::vector<std::vector<Attraction>> visits;

    for (int i = 0; i < n_; ++i) {
        Print(n_, k, i, attractions);

        for (int j = 0; j < k; ++j) {
            ++attractions[j].visits;
        }

        std::sort(attractions.begin(), attractions.end(),
                  [](const Attraction &a1, const Attraction &a2) -> bool {
                      return a1.visits == a2.visits ? a1.popularity > a2.popularity : a1.visits < a2.visits;
                  });

        visits.emplace_back(attractions);

        if (IsSame(attractions)) {
            Print(n_, k, i + 1, attractions);
            break;
        }
    }

    std::cout << visits.size() << std::endl;
    assert(attractions == attractions_);
}

bool Campus::IsSame(const std::vector<Attraction> &attractions) const {
    assert(!attractions.empty() && !attractions_.empty());

    auto visits = attractions[0].visits;
    for (std::size_t i = 0; i < n_; ++i) {
        if (attractions[i] != attractions_[i]) {
            return false;
        }

        if (attractions[i].visits != visits) {
            return false;
        }
    }

    return true;
}

int main() {

    const auto max_n = 50;
    for (int n = 1; n <= max_n; ++n) {
        std::cout << "n = " << n << std::endl;
        for (int k = 1; k <= n; ++k) {
            std::cout << "k = " << k << std::endl;
            Campus(n).Visit(k, 10);
            std::cout << std::endl;
        }
    }

    return 0;
}