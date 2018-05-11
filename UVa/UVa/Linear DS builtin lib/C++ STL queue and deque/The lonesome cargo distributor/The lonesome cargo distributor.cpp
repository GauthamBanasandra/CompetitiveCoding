#include <stdio.h>
#include <stack>
#include <queue>
#include <vector>

using big_int = unsigned long long;

class carrier {
public:
    explicit carrier(const int capacity)
            : capacity_(capacity) {
        current_station = 0;
    }

    bool is_empty() const { return cargo_stack_.empty(); }

    int top() const { return cargo_stack_.top(); }

    void unload() { cargo_stack_.pop(); }

    void load(const int cargo) { cargo_stack_.push(cargo); }

    bool is_vacant() const { return capacity_ - cargo_stack_.size() ? true : false; }

    int current_station;

private:
    int capacity_;
    std::stack<int> cargo_stack_;
};

class station {
public:
    station(const int id, const int platform_capacity)
            : id(id),
              platform_capacity_(platform_capacity) {
    }

    bool is_vacant() const { return platform_capacity_ - platform_.size() ? true : false; }

    void load(const int cargo) { platform_.push(cargo); }

    void unload() { platform_.pop(); }

    bool is_empty() const { return platform_.empty(); }

    int front() const { return platform_.front(); }

    int id;

private:
    int platform_capacity_;
    std::queue<int> platform_;
};

class abcdef {
public:
    abcdef(carrier *carrier, std::vector<station *> *stations, const int misplaced_cargos)
            : clock(0), carrier_(carrier),
              stations_(stations),
              misplaced_cargos_(misplaced_cargos) {
        n_stations_ = static_cast<int>(stations_->size());
    }

    big_int start();

    big_int clock;

private:
    void unload_carrier();

    void load_carrier();

    void move_carrier();

    carrier *carrier_;
    std::vector<station *> *stations_;
    int misplaced_cargos_;
    int n_stations_;
};

void abcdef::unload_carrier() {
    auto &station = stations_->at(carrier_->current_station);
    while (!carrier_->is_empty()) {
        const auto cargo = carrier_->top();
        if (cargo == station->id) {
            carrier_->unload();
            --misplaced_cargos_;
        } else if (station->is_vacant()) {
            carrier_->unload();
            station->load(cargo);
        } else {
            break;
        }

        ++clock;
    }
}

void abcdef::load_carrier() {
    auto station = stations_->at(carrier_->current_station);
    while (!station->is_empty() && carrier_->is_vacant()) {
        carrier_->load(station->front());
        station->unload();
        ++clock;
    }
}

inline void abcdef::move_carrier() {
    carrier_->current_station = (carrier_->current_station + 1) % n_stations_;
    clock += 2;
}

big_int abcdef::start() {
    while (misplaced_cargos_ > 0 || !carrier_->is_empty()) {
        unload_carrier();
        load_carrier();
        move_carrier();
    }

    return clock - 2;
}

int main(int argc, char *argv[]) {
    big_int set;
    int n, s, q, q_i, q_n;
    scanf("%llu", &set);
    while (set--) {
        scanf("%d%d%d", &n, &s, &q);
        carrier carrier(s);
        std::vector<station *> stations(n);
        auto misplaced_cargos = 0;
        for (auto i = 0; i < n; ++i) {
            auto st = new station(i, q);
            scanf("%d", &q_n);
            misplaced_cargos += q_n;
            for (auto j = 0; j < q_n; ++j) {
                scanf("%d", &q_i);
                st->load(q_i - 1);
            }

            stations[i] = st;
        }

        abcdef facility(&carrier, &stations, misplaced_cargos);
        const auto clock = facility.start();
        printf("%llu\n", clock);
        for (auto station : stations) {
            delete station;
        }
    }

    return 0;
}
