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
    ll Estimate(ll amount, ll vacancy, int orders_accepted);

    bool CanFit(ll vacancy, const Order &order, int orders_accepted);
};

ll Estimator::Estimate(ll amount, ll vacancy, int orders_accepted) {
    ll max_amount = 0;
    for (std::size_t i = 0; i < orders.size(); ++i) {
        const auto &order = orders[i];
        if ((orders_accepted & (1 << i)) || !CanFit(vacancy, order, orders_accepted)) {
            continue;
        }

        ll b = Estimate(amount + order.amount, vacancy - order.n_passengers, orders_accepted | (1 << i));
        max_amount = std::max(max_amount, b);
    }

    return std::max(max_amount, amount);
}

bool Estimator::CanFit(ll vacancy, const Order &order, int orders_accepted) {
    if (vacancy - order.n_passengers >= 0) {
        return true;
    }

    for (std::size_t i = 0; i < orders.size(); ++i) {
        if ((orders_accepted & (1 << i)) && (orders[i].to_station <= order.from_station)) {
            vacancy += orders[i].n_passengers;
        }
    }

    return vacancy - order.n_passengers >= 0;
}

inline ll Estimator::Estimate() {
    return Estimate(0, capacity, 0);
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