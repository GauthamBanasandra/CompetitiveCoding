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

bool IsGreater(double x, double y, double epsilon = 0.0000001, ll factor = 10000000) {
    /*x = std::round(x * factor) / factor;
    y = std::round(y * factor) / factor;*/
    return std::abs(x - y) < epsilon;
}

void Print(const std::vector<Point> &points) {
    for (const auto &point : points) {
        std::cout << point.x << " " << point.y << std::endl;
    }
}

struct Radar {
    Radar(const Point &point, ll c) : coverage(c) {
        auto term = std::sqrt((coverage * coverage) - (point.y * point.y));
        h = point.x > 0 ? point.x - term : point.x + term;
    }

    bool IsCovered(const Point &point) const {
        const auto lhs = ((point.x - h) * (point.x - h)) + (point.y * point.y);
        const auto rhs = coverage * coverage;
        return lhs <= rhs;
    }

    double h;
    ll coverage;
};

class RadarInstaller {
public:
    RadarInstaller(const std::vector<Point> &islands, ll radar_coverage);

    ll EstimateRadars() const;

private:
    ll radar_coverage_;
    std::vector<Point> islands_;
};

RadarInstaller::RadarInstaller(const std::vector<Point> &islands, ll radar_coverage) : islands_(islands),
                                                                                       radar_coverage_(radar_coverage) {
    std::sort(islands_.begin(), islands_.end(),
              [](const Point &p1, const Point &p2) -> bool {
                  if (p1.x < p2.x) {
                      return true;
                  }

                  if (p1.x == p2.x) {
                      return p1.y < p2.y;
                  }

                  return false;
              });
}

ll RadarInstaller::EstimateRadars() const {
    auto island_it = islands_.begin();
    if ((*island_it).y > radar_coverage_) {
        return -1;
    }

    Radar radar(*island_it, radar_coverage_);

    ll num_radars = 1;
    for (++island_it; island_it != islands_.end(); ++island_it) {
        if ((*island_it).y > radar_coverage_) {
            return -1;
        }

        if (radar.IsCovered(*island_it)) {
            continue;
        }

        radar = Radar(*island_it, radar_coverage_);
        ++num_radars;
    }

    return num_radars;
}

int main() {
    std::vector<Point> islands{
            {-18, 14},
            {-16, 67},
            {3,   20},
            {-32, 31},
    };


    std::cout << RadarInstaller(islands, 70).EstimateRadars() << std::endl;


    /*ll n, r, x, y, t = 0;
    while (std::cin >> n >> r, n || r) {
        islands.clear();
        islands.reserve(static_cast<std::size_t >(n));

        for (ll i = 0; i < n; ++i) {
            std::cin >> x >> y;
            islands.emplace_back(x, y);
        }

        std::cout << "Case " << (++t) << ": " << RadarInstaller(islands, r).EstimateRadars() << std::endl;
    }
*/
    return 0;
}