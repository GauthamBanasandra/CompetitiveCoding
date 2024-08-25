#include <iostream>
#include <string>
#include <unordered_map>

std::unordered_map<char, std::size_t>
GetFrequencyTable(const std::string &data) {
  std::unordered_map<char, std::size_t> frequency_table;
  for (char c : data) {
    ++frequency_table[c];
  }

  return frequency_table;
}

class Solution {
public:
  bool canConstruct(std::string ransom_note, std::string magazine);
};

bool Solution::canConstruct(std::string ransom_note, std::string magazine) {
  const auto ransom_note_freq_tbl = GetFrequencyTable(ransom_note);
  const auto magazine_freq_tbl = GetFrequencyTable(magazine);

  for (const auto &[key, freq] : ransom_note_freq_tbl) {
    if (magazine_freq_tbl.find(key) == magazine_freq_tbl.end() ||
        freq > magazine_freq_tbl.at(key)) {
      return false;
    }
  }

  return true;
}

int main(int argc, char *argv[]) {
  std::string ransom_note("a");
  std::string magazine("b");
  std::cout << Solution().canConstruct(ransom_note, magazine) << std::endl;

  ransom_note = "aa";
  magazine = "ab";
  std::cout << Solution().canConstruct(ransom_note, magazine) << std::endl;

  ransom_note = "aa";
  magazine = "aab";
  std::cout << Solution().canConstruct(ransom_note, magazine) << std::endl;
}
