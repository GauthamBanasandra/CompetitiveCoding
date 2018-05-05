//
// Created by gauth on 04-05-2018.
//

#include <algorithm>
#include <vector>
#include <string>
#include <deque>
#include <unordered_set>
#include <unordered_map>
#include <cassert>
#include <iostream>

using Exclusions = std::deque<std::pair<std::string, std::string>>;
using Topics = std::vector<std::string>;
using Groups = std::deque<std::deque<std::string>>;

struct TaperingLexicographic {
    bool operator()(const std::string &topic_i, const std::string &topic_j) {
        if (topic_i.length() == topic_j.length()) {
            return topic_i < topic_j;
        }

        return topic_i.length() > topic_j.length();
    }

    bool operator()(const std::deque<std::string> &group_i, const std::deque<std::string> &group_j) {
        const auto n_group = group_i.size();
        assert(n_group == group_j.size());

        for (std::size_t i = 0; i < n_group; ++i) {
            if (group_i[i] == group_j[i]) {
                continue;
            }

            return TaperingLexicographic()(group_i[i], group_j[i]);
        }
    }
};

class CombinationGenerator {
public:
    CombinationGenerator(Topics topics, size_t s,
                         const Exclusions &exclusions);

    void Generate();

private:
    void
    Generate(std::size_t i_topic, std::size_t r, std::unordered_multiset<std::size_t> &exclusions,
             std::deque<std::size_t> &combination,
             Groups &combinations);

    void AddGroup(Groups &groups, const std::deque<std::size_t> &combination);

    const std::size_t s_;
    Topics topics_;
    std::unordered_multimap<std::size_t, std::size_t> exclusions_;
};


void StrToUpper(std::string &str);

void
CombinationGenerator::AddGroup(Groups &groups, const std::deque<std::size_t> &combination) {
    std::deque<std::string> group;
    for (const auto &i_topic : combination) {
        group.emplace_back(topics_[i_topic]);
    }

    std::sort(group.begin(), group.end(), TaperingLexicographic());
    groups.emplace_back(group);
}

CombinationGenerator::CombinationGenerator(Topics topics, const size_t s, const Exclusions &exclusions) : topics_(
        std::move(topics)), s_(s) {
    std::unordered_map<std::string, std::size_t> topic_i_map;
    for (std::size_t i = 0; i < topics_.size(); ++i) {
        topic_i_map[topics_[i]] = i;
    }

    for (const auto &exclusion : exclusions) {
        exclusions_.insert({topic_i_map[exclusion.first], topic_i_map[exclusion.second]});
        exclusions_.insert({topic_i_map[exclusion.second], topic_i_map[exclusion.first]});
    }
}

void
CombinationGenerator::Generate(std::size_t i_topic, std::size_t r, std::unordered_multiset<std::size_t> &exclusions,
                               std::deque<std::size_t> &combination, Groups &combinations) {
    if (i_topic >= topics_.size() || r == 0) {
        if (r == 0) {
            AddGroup(combinations, combination);
        }

        return;
    }

    for (std::size_t i = i_topic; i < topics_.size(); ++i) {
        if (exclusions.find(i) != exclusions.end()) {
            continue;
        }

        auto items_excluded = false;
        auto exclusions_eq = exclusions_.equal_range(i);
        for (auto exclusions_it = exclusions_eq.first; exclusions_it != exclusions_eq.second; ++exclusions_it) {
            exclusions.insert(exclusions_it->second);
            items_excluded = true;
        }

        combination.emplace_back(i);
        Generate(i + 1, r - 1, exclusions, combination, combinations);
        combination.pop_back();

        if (items_excluded) {
            auto exclusions_eq = exclusions_.equal_range(i);
            for (auto exclusions_it = exclusions_eq.first; exclusions_it != exclusions_eq.second; ++exclusions_it) {
                auto exclusion_it = exclusions.find(exclusions_it->second);
                assert(exclusion_it != exclusions.end());

                exclusions.erase(exclusion_it);
            }
        }
    }
}

void CombinationGenerator::Generate() {
    std::unordered_multiset<std::size_t> exclusions;
    std::deque<std::size_t> combination;
    Groups combinations;

    Generate(0, s_, exclusions, combination, combinations);

    std::sort(combinations.begin(), combinations.end(), TaperingLexicographic());
    for (const auto &group : combinations) {
        std::cout << group[0];
        for (std::size_t i = 1; i < group.size(); ++i) {
            std::cout << " " << group[i];
        }

        std::cout << std::endl;
    }
}

void TopicsToUpperCase(Topics &topics) {
    for (auto &topic : topics) {
        StrToUpper(topic);
    }
}

void StrToUpper(std::string &str) {
    for (auto &c : str) {
        c = static_cast<char>(isalpha(c) ? toupper(c) : c);
    }
}

void ExclusionsToUpperCase(Exclusions &exclusions) {
    for (auto &exclusion : exclusions) {
        StrToUpper(exclusion.first);
        StrToUpper(exclusion.second);
    }
}

int main() {
    Topics topics{};
    Exclusions exclusions{};

    int n, t, p, s;
    std::string topic, exclusion_i, exclusion_j;
    std::cin >> n;

    for (int i = 1; i <= n; ++i) {
        topics.clear();
        exclusions.clear();
        std::cin >> t >> p >> s;

        for (int j = 0; j < t; ++j) {
            std::cin >> topic;
            topics.emplace_back(topic);
        }

        for (int j = 0; j < p; ++j) {
            std::cin >> exclusion_i >> exclusion_j;
            exclusions.emplace_back(exclusion_i, exclusion_j);
        }

        TopicsToUpperCase(topics);
        ExclusionsToUpperCase(exclusions);
        printf("Set %d:\n", i);
        CombinationGenerator(topics, s, exclusions).Generate();
        std::cout << std::endl;
    }

    return 0;
}