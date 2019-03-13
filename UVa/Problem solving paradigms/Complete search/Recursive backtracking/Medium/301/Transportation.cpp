//
// Created by gauth on 02-04-2018.
//

#include <algorithm>
#include <vector>
#include <iostream>

using ll = long long;

struct Order {
    Order(int from_station, int to_station, ll n_passengers) : from_station(from_station), to_station(to_station),
                                                               n_passengers(n_passengers),
                                                               amount((to_station - from_station) * n_passengers) {}

    int from_station;
    int to_station;
    ll n_passengers;
    ll amount;
};

class Estimator {
public:
    Estimator(int n_station, ll capacity, std::vector<Order> orders) : n_station(n_station), capacity(capacity),
                                                                       orders(std::move(orders)) {}

    ll Estimate();

    int n_station;
    ll capacity;
    std::vector<Order> orders;

private:
    ll Estimate(std::size_t i, int combination);

    ll GetAmount(int combination);

    bool CanFit(ll vacancy, const Order &order, int orders_accepted);
};

bool Estimator::CanFit(ll vacancy, const Order &order, int orders_accepted) {
    if (vacancy - order.n_passengers >= 0) {
        return true;
    }

    for (std::size_t i = 0; i < orders.size(); ++i) {
        if ((orders_accepted & (1 << i)) &&
            ((orders[i].to_station <= order.from_station) || order.to_station <= orders[i].from_station)) {
            vacancy += orders[i].n_passengers;
        }
    }

    return vacancy - order.n_passengers >= 0;
}

inline ll Estimator::Estimate() {
    return Estimate(0, 0);
}

ll Estimator::Estimate(std::size_t i, int combination) {
    if (i >= orders.size()) {
        return GetAmount(combination);
    }

    auto with = Estimate(i + 1, combination | (1 << i));
    auto without = Estimate(i + 1, combination);
    return std::max(with, without);
}

ll Estimator::GetAmount(int combination) {
    int orders_accepted = 0;
    ll vacancy = capacity, amount = 0;
    for (std::size_t i = 0; i < orders.size(); ++i) {
        const auto &order = orders[i];
        if (!(combination & (1 << i)) || !CanFit(vacancy, order, orders_accepted)) {
            continue;
        }

        vacancy -= order.n_passengers;
        amount += order.amount;
        orders_accepted |= (1 << i);
    }

    return amount;
}

int main() {
    /*std::vector<Order> orders{
            Order{0, 2, 10},
            Order{2, 4, 10}
    };

    std::cout << Estimator(4, 10, orders).Estimate() << std::endl;*/

    ll capacity, n_passengers;
    int n_station, n_order, from_station, to_station;
    std::vector<Order> orders;

    while (std::cin >> capacity >> n_station >> n_order, capacity || n_station || n_order) {
        orders.clear();
        for (int i = 0; i < n_order; ++i) {
            std::cin >> from_station >> to_station >> n_passengers;
            orders.emplace_back(from_station, to_station, n_passengers);
        }

        std::cout << Estimator(n_station, capacity, orders).Estimate() << std::endl;
    }

    return 0;
}