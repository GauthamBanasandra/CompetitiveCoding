#include <iostream>
#include <ios>
#include <algorithm>
#include <string>

#define MAX_ALPHA 200
char alphabets[MAX_ALPHA];
typedef unsigned long long big_int;

bool Compare(char x, char y) {
  return alphabets[x] < alphabets[y];
}

int main(int argc, char *argv[]) {
  std::ios::sync_with_stdio(false);

  big_int test_cases;

  for (int i = 'A', j = 0; i <= 'Z'; ++i) {
    alphabets[i] = j++;
    alphabets[i + 32] = j++;
  }

  scanf("%llu\n", &test_cases);
  while (test_cases--) {
    char in[10000];
    scanf("%s", in);
    std::string word = in;
    sort(word.begin(), word.end(), Compare);
    do {
      printf("%s\n", word.c_str());
    } while (next_permutation(word.begin(), word.end(), Compare));
  }

  return 0;
}
