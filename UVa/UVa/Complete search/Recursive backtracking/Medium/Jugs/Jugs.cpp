//
// Created by gauth on 21-04-2018.
//

#include <vector>
#include <algorithm>
#include <string>
#include <list>
#include <unordered_set>
#include <unordered_map>
#include <cassert>
#include <iostream>
#include <sstream>

enum class JugState {
    k_empty, k_full, k_intermediate
};

enum class Instruction {
    k_fill_a, k_fill_b, k_empty_a, k_empty_b, k_pour_a_b, k_pour_b_a
};

enum class Action {
    k_fill, k_pour_in, k_pour_out, k_empty
};
enum class JugType {
    k_type_a, k_type_b
};

class Jug {
public:
    explicit Jug(const int capacity_) : capacity_(capacity_), level_(0), state_(JugState::k_empty) {}

    inline int GetLevel() const {
        return level_;
    }

    inline JugState GetState() const {
        return state_;
    }

    bool IsPossible(Action action, const Jug &other);

    void PerformAction(Action action, Jug &other);

private:
    bool IsEmpty() const { return level_ == 0; }

    bool IsFull() const { return level_ == capacity_; }

    void Fill();

    void Empty();

    void PourIn(Jug &other);

    void PourOut(Jug &other);

    void UpdateState();

    const int capacity_;
    int level_;
    JugState state_;
};

void Jug::Fill() {
    assert(!IsFull());

    level_ = capacity_;
    state_ = JugState::k_full;
}

void Jug::Empty() {
    assert(!IsEmpty());

    level_ = 0;
    state_ = JugState::k_empty;
}

void Jug::UpdateState() {
    if (IsEmpty()) {
        state_ = JugState::k_empty;
    } else if (IsFull()) {
        state_ = JugState::k_full;
    } else {
        state_ = JugState::k_intermediate;
    }
}

void Jug::PourIn(Jug &other) {
    assert(!IsFull() && !other.IsEmpty());

    const auto quantity = std::min(capacity_ - level_, other.level_);
    level_ += quantity;
    other.level_ -= quantity;

    assert(level_ <= capacity_);
    assert(other.level_ <= other.capacity_);

    UpdateState();
    other.UpdateState();
}

void Jug::PourOut(Jug &other) {
    assert(!IsEmpty() && !other.IsFull());

    const auto quantity = std::min(other.capacity_ - other.level_, level_);
    level_ -= quantity;
    other.level_ += quantity;

    assert(level_ <= capacity_);
    assert(other.level_ <= other.capacity_);

    UpdateState();
    other.UpdateState();
}

bool Jug::IsPossible(const Action action, const Jug &other) {
    switch (state_) {
        case JugState::k_empty:
            switch (action) {
                case Action::k_fill:
                    return true;

                case Action::k_pour_in:
                    return !other.IsEmpty();

                default:
                    return false;
            }

        case JugState::k_full:
            switch (action) {
                case Action::k_pour_out:
                    return !other.IsFull();

                case Action::k_empty:
                    return true;

                default:
                    return false;
            }

        case JugState::k_intermediate:
            switch (action) {
                case Action::k_pour_out:
                    return !other.IsFull();

                case Action::k_pour_in:
                    return !other.IsEmpty();

                case Action::k_fill:
                case Action::k_empty:
                    return true;
            }
    }
}

void Jug::PerformAction(Action action, Jug &other) {
    switch (action) {
        case Action::k_fill:
            Fill();
            break;

        case Action::k_pour_in:
            PourIn(other);
            break;

        case Action::k_pour_out:
            PourOut(other);
            break;

        case Action::k_empty:
            Empty();
            break;
    }
}

struct Tracker {
    using ull = unsigned long long;

public:
    /*inline ull Hash(const Jug &jug_a, const Jug &jug_b) const {
        assert(jug_a.GetLevel() < 10000 && jug_b.GetLevel() < 10000);

        ull hash = 0;
        hash += jug_a.GetLevel() * 10000;
        hash += jug_b.GetLevel();
        return hash;
    }*/

    inline std::string Hash(const Jug &jug_a, const Jug &jug_b) const {
        return std::to_string(jug_a.GetLevel()) + " " + std::to_string(jug_b.GetLevel());
    }

    inline bool IsCycle(const Jug &jug_a, const Jug &jug_b) const {
        return jugs_level.find(Hash(jug_a, jug_b)) != jugs_level.end();
    }

    inline void Add(const Jug &jug_a, const Jug &jug_b) {
        jugs_level.insert(Hash(jug_a, jug_b));
    }

    inline void Remove(const Jug &jug_a, const Jug &jug_b) {
        jugs_level.erase(Hash(jug_a, jug_b));
    }

private:
    std::unordered_set<std::string> jugs_level;
};

class Mixer {
public:
    explicit Mixer(int n_);

    void PrintInstructions(int capacity_jug_a, int capacity_jug_b) const;

private:
    std::string GetStrInstruction(Instruction instruction) const;

    Instruction GetInstruction(Action action, JugType jug_type) const;

    void Mix(Jug &jug_a, Jug &jug_b, Tracker &tracker, std::list<Instruction> &instructions,
             std::list<Instruction> &min_instructions) const;

    const int n_;
    mutable std::unordered_map<JugState, std::list<Action>> transition_;
};

Instruction Mixer::GetInstruction(Action action, JugType jug_type) const {
    switch (jug_type) {
        case JugType::k_type_a:
            switch (action) {
                case Action::k_fill:
                    return Instruction::k_fill_a;

                case Action::k_pour_in:
                    return Instruction::k_pour_b_a;

                case Action::k_pour_out:
                    return Instruction::k_pour_a_b;

                case Action::k_empty:
                    return Instruction::k_empty_a;
            }

        case JugType::k_type_b:
            switch (action) {
                case Action::k_fill:
                    return Instruction::k_fill_b;

                case Action::k_pour_in:
                    return Instruction::k_pour_a_b;

                case Action::k_pour_out:
                    return Instruction::k_pour_b_a;

                case Action::k_empty:
                    return Instruction::k_empty_b;
            }
    }
}

void Mixer::Mix(Jug &jug_a, Jug &jug_b, Tracker &tracker, std::list<Instruction> &instructions,
                std::list<Instruction> &min_instructions) const {
    if (jug_a.GetLevel() == n_ || jug_b.GetLevel() == n_) {
        if (min_instructions.empty() || (instructions.size() < min_instructions.size())) {
            min_instructions = instructions;
        }

        return;
    }

    for (const auto action : transition_[jug_a.GetState()]) {
        if (!jug_a.IsPossible(action, jug_b)) {
            continue;
        }

        Jug temp_jug_a(jug_a);
        Jug temp_jug_b(jug_b);

        temp_jug_a.PerformAction(action, temp_jug_b);
        if (tracker.IsCycle(temp_jug_a, temp_jug_b)) {
            continue;
        }

        tracker.Add(temp_jug_a, temp_jug_b);
        instructions.emplace_back(GetInstruction(action, JugType::k_type_a));

        Mix(temp_jug_a, temp_jug_b, tracker, instructions, min_instructions);

        tracker.Remove(temp_jug_a, temp_jug_b);
        instructions.pop_back();
    }

    for (const auto action : transition_[jug_b.GetState()]) {
        if (!jug_b.IsPossible(action, jug_a)) {
            continue;
        }

        Jug temp_jug_a(jug_a);
        Jug temp_jug_b(jug_b);

        temp_jug_b.PerformAction(action, temp_jug_a);
        if (tracker.IsCycle(temp_jug_a, temp_jug_b)) {
            continue;
        }

        tracker.Add(temp_jug_a, temp_jug_b);
        instructions.emplace_back(GetInstruction(action, JugType::k_type_b));

        Mix(temp_jug_a, temp_jug_b, tracker, instructions, min_instructions);

        tracker.Remove(temp_jug_a, temp_jug_b);
        instructions.pop_back();
    }
}

Mixer::Mixer(const int n_) : n_(n_) {
    transition_[JugState::k_empty] = {Action::k_fill, Action::k_pour_in};
    transition_[JugState::k_intermediate] = {Action::k_pour_out, Action::k_pour_in, Action::k_fill, Action::k_empty};
    transition_[JugState::k_full] = {Action::k_pour_out, Action::k_empty};
}

void Mixer::PrintInstructions(const int capacity_jug_a, const int capacity_jug_b) const {
    Jug jug_a(capacity_jug_a);
    Jug jug_b(capacity_jug_b);
    Tracker tracker;
    std::list<Instruction> instructions;
    std::list<Instruction> min_instructions;

    tracker.Add(jug_a, jug_b);
    Mix(jug_a, jug_b, tracker, instructions, min_instructions);

    for (const auto instruction : min_instructions) {
        std::cout << GetStrInstruction(instruction) << std::endl;
    }

    std::cout << "success" << std::endl;
}

std::string Mixer::GetStrInstruction(Instruction instruction) const {
    switch (instruction) {
        case Instruction::k_fill_a:
            return "fill A";

        case Instruction::k_fill_b:
            return "fill B";

        case Instruction::k_empty_a:
            return "empty A";

        case Instruction::k_empty_b:
            return "empty B";

        case Instruction::k_pour_a_b:
            return "pour A B";

        case Instruction::k_pour_b_a:
            return "pour B A";
    }
}

int main() {
    int capacity_jug_a, capacity_jug_b, n;
    std::string line;

    while (std::getline(std::cin, line), !std::cin.eof()) {
        std::istringstream tokenizer(line);
        tokenizer >> capacity_jug_a >> capacity_jug_b >> n;
        Mixer(n).PrintInstructions(capacity_jug_a, capacity_jug_b);
    }

    return 0;
}