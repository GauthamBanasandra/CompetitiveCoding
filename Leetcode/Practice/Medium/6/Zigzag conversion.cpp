//
// Created by Gautham Banasandra on 22/09/18.
//

#include <string>
#include <vector>
#include <iostream>

class Solution {
 public:
  std::string convert(const std::string &s, std::size_t num_rows);

 private:
  void Adjust(const std::string &str, std::vector<std::string> &v) const;
  std::string Convert(const std::string &str, std::size_t num_rows) const;
  void Fill(const std::string &str, std::vector<std::string> &v) const;
  std::string ReadZigZag(const std::vector<std::string> &v) const;
};

std::string Solution::Convert(const std::string &str, std::size_t num_rows) const {
  if (num_rows == 1) {
    return str;
  }

  std::vector<std::string> v(num_rows);
  Adjust(str, v);

  Fill(str, v);
  return ReadZigZag(v);
}

std::string Solution::convert(const std::string &s, std::size_t num_rows) {
  return Convert(s, num_rows);
}

void Solution::Fill(const std::string &str, std::vector<std::string> &v) const {
  std::size_t i_str = 0, col = 0, row_offset = 0;
  while (i_str < str.length()) {
    for (auto row_it = v.begin() + row_offset; (row_it != v.end()) && (i_str < str.length()); ++row_it) {
      (*row_it)[col] = str[i_str++];
    }
    row_offset = 1;

    for (auto row_it = v.rbegin() + row_offset; (row_it != v.rend()) && (i_str < str.length()); ++row_it) {
      (*row_it)[++col] = str[i_str++];
    }
  }
}

std::string Solution::ReadZigZag(const std::vector<std::string> &v) const {
  std::string zigzag;
  for (const auto &row : v) {
    for (char i : row) {
      if (i == ' ') {
        continue;
      }
      zigzag += i;
    }
  }
  return zigzag;
}

void Solution::Adjust(const std::string &str, std::vector<std::string> &v) const {
  for (std::string &s : v) {
    s.resize(str.length(), ' ');
  }
}

int main() {
  std::cout << Solution().convert("PAYPALISHIRING", 1) << std::endl;
  return 0;
}