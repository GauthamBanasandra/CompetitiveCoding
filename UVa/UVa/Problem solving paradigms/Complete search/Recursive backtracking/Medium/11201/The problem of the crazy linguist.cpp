//
// Created by gauth on 11-05-2018.
//

#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <cassert>

using lf = float;
using ll = long long;

struct SBCTracker {
public:
    SBCTracker() : cum_sbc_(0.0), n_words_(0) {}

    void Add(lf sbc);

    lf GetMean() const;

private:
    lf cum_sbc_;
    ll n_words_;
};

void SBCTracker::Add(lf sbc) {
    assert(sbc >= 0);

    cum_sbc_ += sbc;
    ++n_words_;
}

lf SBCTracker::GetMean() const {
    assert(n_words_ > 0);
    return cum_sbc_ / n_words_;
}

struct ConstraintTracker {
public:
    void Use(char c) { ++frequency_[c]; }

    void UndoUse(char c);

    bool WillExceed(char c) { return frequency_[c] >= 2; }

private:
    std::unordered_map<char, int> frequency_;
};

void ConstraintTracker::UndoUse(char c) {
    --frequency_[c];

    assert(frequency_[c] >= 0);
}

class SBC {
public:
    explicit SBC(std::string word);

    bool IsSBCGreaterOrEqualToAll();

    static std::unordered_map<char, lf> vowels, consonants;
    static std::unordered_map<std::size_t, lf> sbc_cache;

private:

    void EvaluateAllSBC(std::size_t i_word, lf w_sbc, SBCTracker &sbc_tracker, ConstraintTracker &constraint_tracker);

    lf EvaluateSBC(const std::string &word);

    std::string word_;
};

inline std::size_t Hash(char c, std::size_t n) {
    return static_cast<int>(c) * 10000 + n;
}

std::unordered_map<char, lf> SBC::vowels;
std::unordered_map<char, lf> SBC::consonants;
std::unordered_map<std::size_t, lf> SBC::sbc_cache;

void SBC::EvaluateAllSBC(std::size_t i_word, lf w_sbc, SBCTracker &sbc_tracker, ConstraintTracker &constraint_tracker) {
    if (i_word >= word_.length()) {
        sbc_tracker.Add(w_sbc);
        return;
    }

    for (const auto kv : (i_word + 1) & 1 ? consonants : vowels) {
        if (constraint_tracker.WillExceed(kv.first)) {
            continue;
        }

        constraint_tracker.Use(kv.first);
        EvaluateAllSBC(i_word + 1, w_sbc + (i_word + 1) * kv.second, sbc_tracker, constraint_tracker);
        constraint_tracker.UndoUse(kv.first);
    }
}

lf SBC::EvaluateSBC(const std::string &word) {
    assert(!word.empty());

    lf cum_sbc = 0;
    for (std::size_t i = 0; i < word.length(); ++i) {
        cum_sbc += (i + 1) * ((i + 1) & 1 ? consonants[word[i]] : vowels[word[i]]);
    }

    return cum_sbc;
}

SBC::SBC(std::string word) : word_(std::move(word)) {
    vowels = {
            {'a', 12.53},
            {'e', 13.68},
            {'i', 6.25},
            {'o', 8.68},
            {'u', 3.93}
    };

    consonants = {
            {'b', 1.42},
            {'c', 4.68},
            {'d', 5.86},
            {'f', 0.69},
            {'g', 1.01},
            {'h', 0.70},
            {'j', 0.44},
            {'k', 0.00},
            {'l', 4.97},
            {'m', 3.15},
            {'n', 6.71},
            {'p', 2.51},
            {'q', 0.88},
            {'r', 6.87},
            {'s', 7.98},
            {'t', 4.63},
            {'v', 0.90},
            {'w', 0.02},
            {'x', 0.22},
            {'y', 0.90},
            {'z', 0.52},
    };

    assert(vowels.size() + consonants.size() == 26);
}

bool SBC::IsSBCGreaterOrEqualToAll() {
    auto hash = Hash(word_[0], word_.length());

    auto sbc_cache_find = sbc_cache.find(hash);
    if (sbc_cache_find != sbc_cache.end()) {
        return EvaluateSBC(word_) >= sbc_cache_find->second;
    }

    SBCTracker sbc_tracker;
    ConstraintTracker constraint_tracker;

    EvaluateAllSBC(1, consonants[word_[0]], sbc_tracker, constraint_tracker);

    auto mean = sbc_tracker.GetMean();
    sbc_cache[hash] = mean;
    return EvaluateSBC(word_) >= mean;
}

int main() {
    ll t;
    std::string word;

    std::cin >> t;
    while (t-- > 0) {
        std::cin >> word;
        std::cout << (SBC(word).IsSBCGreaterOrEqualToAll() ? "above or equal" : "below") << std::endl;
    }

    return 0;
}