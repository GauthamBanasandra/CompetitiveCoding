//
// Created by gautham on 13/8/18.
//

#include <iostream>
#include <queue>
#include <string>
#include <cassert>
#include <ios>

using LexicographicOrder = std::priority_queue<char, std::vector<char>, std::greater<char>>;

struct Alphabet {
  Alphabet() : name('\0'), value(-1) {}
  Alphabet(char name, int value) : name(name), value(value) {}

  bool operator<(const Alphabet &other) const {
    return value == other.value ? name > other.name : value > other.value;
  }

  char name;
  int value;
};

class Numerology {
 public:
  Numerology();
  std::string GetName(std::size_t max_length);

 private:
  void HandleAlphabet(std::priority_queue<Alphabet> &alphabets,
                      LexicographicOrder &to_alphabets,
                      int &num_left,
                      int max_num_left);

  std::string GetName(LexicographicOrder &vowels, LexicographicOrder &consonants) const;

  const int max_vowels_;
  const int max_consonants_;
  std::priority_queue<Alphabet> vowels_;
  std::priority_queue<Alphabet> consonants_;
};

Numerology::Numerology() : max_consonants_(5), max_vowels_(21) {
  for (int c = 'A', i = 0; c < 'A' + 26; ++c, ++i) {
    switch (static_cast<char>(c)) {
      case 'A':
      case 'E':
      case 'I':
      case 'O':
      case 'U':vowels_.emplace(static_cast<char>(c), (i % 9) + 1);
        break;

      default:consonants_.emplace(static_cast<char>(c), (i % 9) + 1);
    }
  }
}

std::string Numerology::GetName(std::size_t max_length) {
  int num_vowels_left = max_vowels_;
  int num_consonants_left = max_consonants_;
  LexicographicOrder vowels;
  LexicographicOrder consonants;

  for (std::size_t i = 0; i < max_length; ++i) {
    if ((i + 1) & 1) {
      HandleAlphabet(vowels_, vowels, num_vowels_left, max_vowels_);
    } else {
      HandleAlphabet(consonants_, consonants, num_consonants_left, max_consonants_);
    }
  }

  return GetName(vowels, consonants);
}

void Numerology::HandleAlphabet(std::priority_queue<Alphabet> &alphabets,
                                LexicographicOrder &to_alphabets,
                                int &num_left,
                                const int max_num_left) {
  assert(!alphabets.empty());
  assert(num_left > 0);

  to_alphabets.emplace(alphabets.top().name);
  --num_left;

  if (num_left == 0) {
    num_left = max_num_left;
    alphabets.pop();
  }
}

std::string Numerology::GetName(LexicographicOrder &vowels, LexicographicOrder &consonants) const {
  std::string name(vowels.size() + consonants.size(), 'x');

  for (int i = 0; !vowels.empty(); ++i) {
    if (i & 1) {
      continue;
    }
    assert(i < name.length());

    name[i] = vowels.top();
    vowels.pop();
  }

  for (int i = 0; !consonants.empty(); ++i) {
    if ((i & 1) == 0) {
      continue;
    }
    assert(i < name.length());

    name[i] = consonants.top();
    consonants.pop();
  }

  return name;
}

int main() {
  std::ios::sync_with_stdio(false);
  
  int n = 0;
  std::size_t max_length = 0;

  std::cin >> n;
  for (int i = 1; i <= n; ++i) {
    std::cin >> max_length;
    std::cout << "Case " << i << ": " << Numerology().GetName(max_length) << std::endl;
  }

  return 0;
}