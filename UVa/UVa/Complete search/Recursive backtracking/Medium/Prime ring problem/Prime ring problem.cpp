//
// Created by gauth on 17-04-2018.
//

#include <cstdlib>
#include <vector>
#include <string>
#include <sstream>
#include <cassert>
#include <unordered_set>
#include <iostream>

struct RingUsageTracker {
    RingUsageTracker() : ring(0) {}

    void Use(int i) {
        assert(i <= 16);
        --i;
        assert(i >= 0);
        ring |= (1 << i);
    }

    void UndoUse(int i) {
        assert(i <= 16);
        --i;
        assert(i >= 0);
        ring &= ~(1 << i);
    }

    bool IsUsed(int i) {
        assert(i <= 16);
        --i;
        assert(i >= 0);
        return static_cast<bool>(ring & (1 << i));
    }

    int ring;
};

using Ring = std::vector<int>;

class PrimeRing {
public:
    explicit PrimeRing(int n) : n(n) {}

    void Solve();

private:
    bool IsPrime(int number);

    void FillNextRing(Ring &ring, int i_ring, RingUsageTracker &tracker);

    void PrintRing(const std::vector<int> &ring) const;

    int n;
    static std::unordered_set<int> prime_numbers;
};

std::unordered_set<int> PrimeRing::prime_numbers{2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67,
                                                 71, 73, 79, 83, 89, 97, 101};

inline bool PrimeRing::IsPrime(int number) {
    assert(number < 102);
    return prime_numbers.find(number) != prime_numbers.end();
}

void
PrimeRing::FillNextRing(Ring &ring, int i_ring, RingUsageTracker &tracker) {
    if (i_ring >= n) {
        if (!IsPrime(ring[0] + ring[i_ring - 1])) {
            return;
        }

        PrintRing(ring);
        return;
    }

    for (int i = 2; i <= n; ++i) {
        if (tracker.IsUsed(i) || !IsPrime(ring[i_ring - 1] + i)) {
            continue;
        }

        tracker.Use(i);
        ring[i_ring] = i;

        FillNextRing(ring, i_ring + 1, tracker);

        tracker.UndoUse(i);
    }
}

void PrimeRing::Solve() {
    Ring ring(n, 1);
    RingUsageTracker tracker;

    tracker.Use(1);
    FillNextRing(ring, 1, tracker);
}

void PrimeRing::PrintRing(const std::vector<int> &ring) const {
    assert(!ring.empty());
    std::ostringstream arrangement;

    arrangement << ring[0];
    for (std::size_t i = 1; i < n; ++i) {
        arrangement << " " << ring[i];
    }

    std::cout << arrangement.str() << std::endl;
}

int main() {
    int t = 1;
    std::string line;

    while (std::getline(std::cin, line), !std::cin.eof()) {
        if (t > 1) {
            std::cout << std::endl;
        }

        printf("Case %d:\n", t++);
        PrimeRing(atoi(line.c_str())).Solve();
    }

    return 0;
}