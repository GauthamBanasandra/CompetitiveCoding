//
// Created by Gautham on 04-12-2018.
//

#include <iostream>
#include <vector>
#include <ios>

class Primes {
 public:
  explicit Primes(const std::vector<int> &primes, std::size_t k, std::size_t max_num);

  int Count(std::size_t k, int s);

 private:
  int Count(std::size_t i, std::size_t k, int s);

  const std::vector<int> &primes_;
  std::vector<std::vector<std::vector<int>>> memo_;
};

Primes::Primes(const std::vector<int> &primes, std::size_t k, std::size_t max_num) : primes_(primes) {
  memo_.resize(primes.size());
  for (auto &memo_k : memo_) {
    memo_k.resize(k + 1);
    for (auto &memo_num : memo_k) {
      memo_num.resize(max_num + 1, -1);
    }
  }

  Count(k, static_cast<int>(max_num));
}

int Primes::Count(std::size_t i, std::size_t k, int s) {
  if (i >= primes_.size()) {
    return 0;
  }

  if (k == 0 && s == 0) {
    return 1;
  }

  if ((k != 0 && s == 0) || (k == 0 && s != 0)) {
    return 0;
  }

  if (primes_[i] > s) {
    return Count(i + 1, k, s);
  }

  auto &memo = memo_[i][k][s];
  if (memo != -1) {
    return memo;
  }

  return memo = Count(i + 1, k, s) + Count(i + 1, k - 1, s - primes_[i]);
}

int Primes::Count(std::size_t k, int s) {
  return Count(0, k, s);
}

int main() {
  std::ios::sync_with_stdio(false);

  int num = 0;
  std::size_t max_k = 14, max_num = 1120, k = 0;
  std::vector<int> primes_list
      {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107,
       109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229,
       233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359,
       367, 373, 379, 383, 389, 397, 401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491,
       499, 503, 509, 521, 523, 541, 547, 557, 563, 569, 571, 577, 587, 593, 599, 601, 607, 613, 617, 619, 631, 641,
       643, 647, 653, 659, 661, 673, 677, 683, 691, 701, 709, 719, 727, 733, 739, 743, 751, 757, 761, 769, 773, 787,
       797, 809, 811, 821, 823, 827, 829, 839, 853, 857, 859, 863, 877, 881, 883, 887, 907, 911, 919, 929, 937, 941,
       947, 953, 967, 971, 977, 983, 991, 997, 1009, 1013, 1019, 1021, 1031, 1033, 1039, 1049, 1051, 1061, 1063, 1069,
       1087, 1091, 1093, 1097, 1103, 1109, 1117, 1123};

  Primes primes(primes_list, max_k, max_num);

  while (std::cin >> num >> k, num || k) {
    std::cout << primes.Count(k, num) << std::endl;
  }
  return 0;
}