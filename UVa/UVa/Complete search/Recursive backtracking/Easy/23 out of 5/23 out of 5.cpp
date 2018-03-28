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

  int count = 0;
  int expression_result;
  std::vector<int> numbers;
  std::vector<Operators> operators;

 private:
  bool Construct(int i_opr, int i_num, int result);
};

bool ExpressionConstructor::Construct(int i_opr, int i_num, int result) {
  if (i_opr > operators.size()) {
    std::cout << ++count << " : " << result << std::endl;
    return result == expression_result;
  }

  for (auto &i : operators) {
    switch (i) {
      case Operators::k_add:result += numbers[i_num + 1];
        break;

      case Operators::k_multiply:result *= numbers[i_num + 1];
        break;

      case Operators::k_subtract:result -= numbers[i_num + 1];
        break;
    }

    if (Construct(i_opr + 1, i_num + 1, result)) {
      return true;
    }
  }

  return false;
}

bool ExpressionConstructor::Construct() {
  return Construct(0, 0, numbers[0]);
}

int main() {
  std::vector<int> numbers{1, 2, 3, 4, 5};
  std::vector<Operators> operators{Operators::k_add, Operators::k_multiply, Operators::k_subtract};
  if (ExpressionConstructor(23, numbers, operators).Construct()) {
    std::cout << "Possible" << std::endl;
  } else {
    std::cout << "Impossible" << std::endl;
  }

  return 0;
}