#include <vector>
#include <unordered_map>
#include <list>
#include <iostream>
#include <string>

void print(const std::unordered_map<std::size_t, std::size_t> &tree_size);

namespace ds {
    class ufds {
    public:
        explicit ufds(std::size_t size);

        std::size_t find_set(std::size_t i);

        bool is_same_set(std::size_t i, std::size_t j);

        std::size_t union_set(std::size_t i, std::size_t j);

        std::size_t size;
        std::vector<std::size_t> parent_index;
        std::vector<std::size_t> rank;
        std::unordered_map<std::size_t, std::size_t> tree_size;
    };

    inline ufds::ufds(const std::size_t size) : size(size) {
        rank.assign(size, 0);

        for (std::size_t i = 0; i < size; ++i) {
            parent_index.emplace_back(i);
            tree_size[i] = 1;
        }
    }

    inline std::size_t ufds::find_set(const std::size_t i) {
        if (parent_index[i] == i) {
            return i;
        }

        parent_index[i] = find_set(parent_index[i]);
        return parent_index[i];
    }

    inline bool ufds::is_same_set(const std::size_t i, const std::size_t j) {
        return find_set(i) == find_set(j);
    }

    inline std::size_t ufds::union_set(const std::size_t i, const std::size_t j) {
        const auto parent_i = find_set(i);
        if (!is_same_set(i, j)) {
            const auto parent_j = find_set(j);
            if (rank[parent_i] > rank[parent_j]) {
                parent_index[parent_j] = parent_i;
                const auto parent_j_size = tree_size.find(parent_j);
                tree_size[parent_i] += parent_j_size->second;
                tree_size.erase(parent_j_size);
                return parent_i;
            }

            parent_index[parent_i] = parent_j;
            const auto parent_i_size = tree_size.find(parent_i);
            tree_size[parent_j] += parent_i_size->second;
            tree_size.erase(parent_i_size);

            if (rank[parent_i] == rank[parent_j]) {
                ++rank[parent_j];
            }

            return parent_j;
        }

        return parent_i;
    }
}

inline void assign_index(const std::string &person, std::unordered_map<std::string, std::size_t> &people) {
    if (people.find(person) == people.end()) {
        people[person] = people.size();
    }
}

int main(int argc, char *argv[]) {
    std::size_t n, e;
    std::string f1, f2;
    std::list<std::pair<std::string, std::string>> friendships;
    std::unordered_map<std::string, std::size_t> people;

    std::cin >> n;
    while (n--) {
        friendships.clear();
        people.clear();

        std::cin >> e;
        while (e--) {
            std::cin >> f1 >> f2;

            assign_index(f1, people);
            assign_index(f2, people);
            friendships.emplace_back(f1, f2);
        }

        ds::ufds social_network(people.size());
        for (const auto &friends : friendships) {
            const auto &network_id = social_network.union_set(people[friends.first], people[friends.second]);
            std::cout << social_network.tree_size[network_id] << std::endl;
        }
    }

    return 0;
}
