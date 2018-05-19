#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include <vector>
#include <unordered_map>

using big_int = long long;

std::string courses_key(const std::vector<int> &courses) {
    std::string courses_key;
    for (auto c : courses) {
        courses_key += std::to_string(c) + " ";
    }

    return courses_key;
}

int main(int argc, char *argv[]) {
    int n, course, most_popular_course_count = 0, conformity = 0;
    std::string line;
    std::vector<int> courses;
    std::unordered_map<std::string, int> course_popularity;

    while (scanf("%d\n", &n), n != 0) {
        course_popularity.clear();
        conformity = most_popular_course_count = 0;
        while (n--) {
            getline(std::cin, line);
            std::istringstream buf(line);
            courses.clear();
            while (buf >> course) {
                courses.push_back(course);
            }

            sort(courses.begin(), courses.end());

            const auto &ckey = courses_key(courses);
            ++course_popularity[ckey];
            if (course_popularity[ckey] > most_popular_course_count) {
                most_popular_course_count = course_popularity[ckey];
            }
        }

        for (const auto &popularity : course_popularity) {
            if (popularity.second == most_popular_course_count) {
                conformity += popularity.second;
            }
        }

        std::cout << conformity << std::endl;
    }

    return 0;
}
