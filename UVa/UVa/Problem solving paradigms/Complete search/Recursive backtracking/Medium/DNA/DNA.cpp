//
// Created by gauth on 12-05-2018.
//

#include <string>
#include <iostream>
#include <unordered_set>
#include <vector>
#include <cassert>

class DNA {
public:
    DNA(std::string dna, int k) : dna_(std::move(dna)), k_(k), nucleotides_("AGCT") { assert(k <= dna_.length()); }

    void PrintMutations() const;

private:
    void Mutations(std::size_t i_dna, int k, std::string &dna, std::unordered_set<std::string> &mutations) const;

    const std::string dna_, nucleotides_;
    const int k_;
};

void DNA::Mutations(std::size_t i_dna, int k, std::string &dna, std::unordered_set<std::string> &mutations) const {
    if (i_dna >= dna_.length() || k == 0) {
        if (k == 0) {
            mutations.insert(dna);
        }

        return;
    }

    for (std::size_t i = i_dna; i < dna_.length(); ++i) {
        for (const auto nucleotide : nucleotides_) {
            dna[i] = nucleotide;
            Mutations(i + 1, k - 1, dna, mutations);
        }

        dna[i] = dna_[i];
    }
}

void DNA::PrintMutations() const {
    std::string dna(dna_);
    std::unordered_set<std::string> unique_mutations;

    Mutations(0, k_, dna, unique_mutations);

    std::vector<std::string> mutations(unique_mutations.begin(), unique_mutations.end());
    std::sort(mutations.begin(), mutations.end());

    std::cout << mutations.size() << std::endl;
    for (const auto &mutation : mutations) {
        std::cout << mutation << std::endl;
    }
}

int main() {
    int t, n, k;
    std::string dna;

    std::cin >> t;
    while (t-- > 0) {
        std::cin >> n >> k >> dna;
        DNA(dna, k).PrintMutations();
    }

    return 0;
}