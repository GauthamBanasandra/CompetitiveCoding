//
// Created by gauth on 27-04-2018.
//

// WA

#include <string>
#include <vector>
#include <set>
#include <unordered_map>
#include <iostream>
#include <cassert>

using BundledNewspapers = std::unordered_map<std::size_t, std::set<std::string>>;

class Newspapers {
public:
    Newspapers(const std::size_t bundle_start_, const std::size_t bundle_end_,
               const std::vector<std::string> &newspapers_) : from_bundle_size_(bundle_start_),
                                                              to_bundle_size(bundle_end_),
                                                              newspapers_(newspapers_),
                                                              n_newspapers_(newspapers_.size()) {}

    void PrintBundle();

private:
    void Bundle(std::size_t i_newspaper, std::vector<std::size_t> &bundle, BundledNewspapers &bundles);

    void AddBundle(const std::vector<std::size_t> &bundle, BundledNewspapers &bundles);

    const std::size_t n_newspapers_, from_bundle_size_, to_bundle_size;
    const std::vector<std::string> newspapers_;
};

void Newspapers::Bundle(std::size_t i_newspaper, std::vector<std::size_t> &bundle, BundledNewspapers &bundles) {
    if (i_newspaper >= n_newspapers_) {
        if (bundle.size() >= from_bundle_size_ && bundle.size() <= to_bundle_size) {
            AddBundle(bundle, bundles);
        }

        return;
    }

    bundle.emplace_back(i_newspaper);
    Bundle(i_newspaper + 1, bundle, bundles);
    bundle.pop_back();

    Bundle(i_newspaper + 1, bundle, bundles);
}

void Newspapers::AddBundle(const std::vector<std::size_t> &bundle, BundledNewspapers &bundles) {
    assert(!bundle.empty());

    std::string bundle_str = newspapers_[bundle[0]];
    for (std::size_t i = 1; i < bundle.size(); ++i) {
        bundle_str += ", " + newspapers_[bundle[i]];
    }

    bundles[bundle.size()].insert(bundle_str);
}

void Newspapers::PrintBundle() {
    std::vector<std::size_t> bundle;
    BundledNewspapers bundles;

    Bundle(0, bundle, bundles);

    for (auto bundle_size = from_bundle_size_; bundle_size <= to_bundle_size; ++bundle_size) {
        printf("Size %ld\n", bundle_size);
        for (const auto &newspapers : bundles[bundle_size]) {
            std::cout << newspapers << std::endl;
        }

        std::cout << std::endl;
    }
}

int main() {

    int m;
    std::size_t a, b;
    std::string line;
    std::vector<std::string> newspapers;

    std::cin >> m;
    for (int i = 0; i < m; ++i) {
        newspapers.clear();
        std::cin >> a >> b;
        std::cin.ignore();

        while (std::getline(std::cin, line), !line.empty()) {
            newspapers.emplace_back(line);
        }

        if (i > 0) {
            std::cout << std::endl;
        }

        std::sort(newspapers.begin(), newspapers.end());
        Newspapers(a, b, newspapers).PrintBundle();
    }

    return 0;
}