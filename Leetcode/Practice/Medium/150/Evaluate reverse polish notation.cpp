#include <cassert>
#include <cctype>
#include <iostream>
#include <stack>
#include <string>
#include <vector>

int EvaluateRPN(const std::vector<std::string> &tokens) {
  std::stack<int> evaluations;

  const auto get_operands = [&]() -> std::pair<int, int> {
    const auto operand2 = evaluations.top();
    evaluations.pop();
    const auto operand1 = evaluations.top();
    evaluations.pop();
    return {operand1, operand2};
  };

  for (const auto &token : tokens) {
    if (token.size() > 1 || std::isdigit(token[0])) {
      evaluations.push(std::stoi(token));
      continue;
    }

    switch (token[0]) {
    case '+': {
      const auto operands = get_operands();
      evaluations.push(operands.first + operands.second);
    } break;

    case '-': {
      const auto operands = get_operands();
      evaluations.push(operands.first - operands.second);
    } break;

    case '*': {
      const auto operands = get_operands();
      evaluations.push(operands.first * operands.second);
    } break;

    case '/': {
      const auto operands = get_operands();
      evaluations.push(operands.first / operands.second);
    } break;

    default:
      assert(false);
    }
  }

  assert(evaluations.size() == 1);
  return evaluations.top();
}

class Solution {
public:
  static int evalRPN(std::vector<std::string> &tokens);
};

int Solution::evalRPN(std::vector<std::string> &tokens) {
  return EvaluateRPN(tokens);
}

int main(int argc, char *argv[]) {
  std::vector<std::string> tokens{"10", "6", "9",  "3", "+", "-11", "*",
                                  "/",  "*", "17", "+", "5", "+"};
  std::cout << Solution::evalRPN(tokens) << std::endl;
  return 0;
}
