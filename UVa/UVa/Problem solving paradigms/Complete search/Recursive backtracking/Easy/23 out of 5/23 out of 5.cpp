//
// Created by gauth on 28-03-2018.
//

#include <utility>
#include <vector>
#include <iostream>

enum class Operators { k_add, k_multiply, k_subtract };

class ExpressionConstructor {
 public:
  ExpressionConstructor(int expression_result, std::vector<int> numbers, std::vector<Operators> operators)
      : expression_result(expression_result), numbers(std::move(numbers)), operators(std::move(operators)) {}

  bool Construct();

  int expression_result;
  std::vector<int> numbers;
  std::vector<Operators> operators;

 private:
  int PerformOperation(int left_operand, int right_operand, Operators op);
  bool Construct(int i_opr, int i_num, int result);
};

bool ExpressionConstructor::Construct(int i_opr, int i_num, int result) {
  if (i_opr > operators.size()) {
    return result == expression_result;
  }

  for (auto &i : operators) {
    auto operation = PerformOperation(result, numbers[i_num + 1], i);
    if (Construct(i_opr + 1, i_num + 1, operation)) {
      return true;
    }
  }

  return false;
}

bool ExpressionConstructor::Construct() {
  return Construct(0, 0, numbers[0]);
}

inline int ExpressionConstructor::PerformOperation(int left_operand,
                                                   int right_operand,
                                                   Operators op) {
  switch (op) {
    case Operators::k_add: return left_operand + right_operand;
    case Operators::k_multiply:return left_operand * right_operand;
    case Operators::k_subtract:return left_operand - right_operand;
  }
}

int main() {
  std::vector<int> numbers;
  std::vector<Operators> operators{Operators::k_add, Operators::k_multiply, Operators::k_subtract};

  while (true) {
    numbers.clear();
    bool all_zero = true;
    for (int i = 0; i < 5; ++i) {
      static int number = 0;
      std::cin >> number;
      numbers.emplace_back(number);
      if (number) {
        all_zero = false;
      }
    }

    if (all_zero) {
      break;
    }

    std::sort(numbers.begin(), numbers.end());
    bool is_possible = false;
    do {
      if (ExpressionConstructor(23, numbers, operators).Construct()) {
        is_possible = true;
        break;
      }
    } while (std::next_permutation(numbers.begin(), numbers.end()));

    std::cout << (is_possible ? "Possible" : "Impossible") << std::endl;
  }

  return 0;
}