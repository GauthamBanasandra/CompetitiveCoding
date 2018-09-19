#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <sstream>
#include <vector>
#include <cassert>
#include <algorithm>

int main(int argc, char *argv[]) {
  std::ios::sync_with_stdio(false);

  std::string line, word, key;
  std::unordered_map<std::string, std::pair<bool, std::string>> an_status;
  std::unordered_set<std::string> words;

  while (getline(std::cin, line), line != "#") {
    std::istringstream buf(line);
    while (buf >> word) {
      key.resize(word.size());
      transform(word.begin(), word.end(), key.begin(), toupper);
      sort(key.begin(), key.end());

      const auto find_an = an_status.find(key);
      if (find_an == an_status.end()) {
        an_status[key] = make_pair(true, word);
        assert(words.find(word) == words.end());
        words.insert(word);
      } else if (find_an->second.first) {
        find_an->second.first = false;
        assert(words.find(find_an->second.second) != words.end());
        words.erase(find_an->second.second);
      }
    }
  }

  std::vector<std::string> sorted_words(words.begin(), words.end());
  sort(sorted_words.begin(), sorted_words.end());
  for (auto w : sorted_words) {
    printf("%s\n", w.c_str());
  }

  return 0;
}
