//
// Created by gauth on 07-04-2018.
//

#include <string>
#include <iostream>
#include <cassert>
#include <utility>

using ll = long long;

struct BattleInfo {
    BattleInfo(bool is_impossible, ll hack_count) : is_impossible(is_impossible), hack_count(hack_count) {}

    bool is_impossible;
    ll hack_count;
};

class Battle {
public:
    Battle(std::string program, ll shield) : program(std::move(program)), shield(shield), damage(EstimateDamage()) {}

    BattleInfo Begin();

private:
    ll EstimateDamage() const;

    bool Hack();

    std::string program;
    ll shield, damage;
};

ll Battle::EstimateDamage() const {
    ll charge = 1, damage = 0;

    for (const auto &v_program : program) {
        switch (v_program) {
            case 'C':
                charge *= 2;
                break;

            case 'S':
                damage += charge;
                break;

            default:
                // Unknown instruction
                assert(false);
                break;
        }
    }

    return damage;
}

bool Battle::Hack() {
    auto i_charge = program.rfind("CS");
    if (i_charge == std::string::npos) {
        return false;
    }

    auto i_shoot = i_charge + 1;
    auto t = program[i_charge];
    program[i_charge] = program[i_shoot];
    program[i_shoot] = t;
    return true;
}

BattleInfo Battle::Begin() {
    BattleInfo info{true, 0};

    while (damage > shield) {
        auto hack_success = Hack();
        info.hack_count = (hack_success ? info.hack_count + 1 : info.hack_count);

        damage = EstimateDamage();
        if (!hack_success && (damage > shield)) {
            return info;
        }
    }

    info.is_impossible = false;
    return info;
}

int main() {
    int t;
    ll d;
    std::string p;

    std::cin >> t;
    for (int i = 1; i <= t; ++i) {
        std::cin >> d >> p;

        printf("Case #%d: ", i);
        auto battle_info = Battle(p, d).Begin();
        if (battle_info.is_impossible) {
            std::cout << "IMPOSSIBLE" << std::endl;
        } else {
            std::cout << battle_info.hack_count << std::endl;
        }
    }

    return 0;
}