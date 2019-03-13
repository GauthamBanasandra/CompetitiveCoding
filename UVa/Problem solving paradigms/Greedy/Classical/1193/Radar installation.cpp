//
// Created by gauth on 05-07-2018.
//

// WA
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>

using ll = long long;

struct Point {
    Point() : x(0), y(0) {}

    Point(ll x, ll y) : x(x), y(y) {}

    ll x;
    ll y;
};

struct Range {
    Range() : start(0.0), end(0.0) {}

    Range(const Point &point, ll radius);

    bool operator<(const Range &other) const {
        return end == other.end ? start < other.start : end < other.end;
    }

    double start;
    double end;
};

Range::Range(const Point &point, ll radius) {
    auto term = std::sqrt((radius * radius) - (point.y * point.y));
    start = point.x - term;
    end = point.x + term;
}

void Print(const std::vector<Point> &points) {
    for (const auto &point : points) {
        std::cout << point.x << " " << point.y << std::endl;
    }
}

class RadarInstaller {
public:
    RadarInstaller(const std::vector<Point> &islands, ll radar_coverage) : radar_coverage_(radar_coverage),
                                                                           islands_(islands) {}

    ll EstimateRadars() const;

private:
    ll radar_coverage_;
    std::vector<Point> islands_;
};

ll RadarInstaller::EstimateRadars() const {
    std::vector<Range> ranges;
    ranges.reserve(islands_.size());

    for (const auto &island : islands_) {
        if (island.y > radar_coverage_) {
            return -1;
        }

        ranges.emplace_back(island, radar_coverage_);
    }

    std::sort(ranges.begin(), ranges.end());
    ll num_radars = 0;
    for (std::size_t i = 0; i < ranges.size();) {
        std::size_t j = 0;
        for (j = i; j < ranges.size(); ++j) {
            if (ranges[j].start > ranges[i].end) {
                break;
            }
        }

        i = j;
        ++num_radars;
    }

    return num_radars;
}

int main() {
    ll n, r, x, y, t = 0;
    std::vector<Point> islands;

    while (std::cin >> n >> r, n || r) {
        islands.clear();
        islands.reserve(static_cast<std::size_t >(n));

        for (ll i = 0; i < n; ++i) {
            std::cin >> x >> y;
            islands.emplace_back(x, y);
        }

        std::cout << "Case " << (++t) << ": " << RadarInstaller(islands, r).EstimateRadars() << std::endl;
    }
    return 0;
}