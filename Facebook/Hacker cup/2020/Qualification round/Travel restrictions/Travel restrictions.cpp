#include <cassert>
#include <cmath>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>

namespace fb_qualification_round_2020 {
class FlightPlanner {
public:
  FlightPlanner(size_t num_nodes, const std::string &incoming_restrictions,
                const std::string &outgoing_restrictions);

  const std::vector<std::string> &GetPlan();

private:
  const size_t num_nodes_;
  std::vector<std::string> adj_matrix_;
};

FlightPlanner::FlightPlanner(const size_t num_nodes,
                             const std::string &incoming_restrictions,
                             const std::string &outgoing_restrictions)
    : num_nodes_{num_nodes} {
  adj_matrix_.resize(num_nodes_, std::string(num_nodes_, 'N'));

  for (size_t i = 0; i < num_nodes_; ++i) {
    for (size_t j = 0; j < num_nodes_; ++j) {
      if (std::llabs(static_cast<long long>(i) - static_cast<long long>(j)) <=
          1L) {
        adj_matrix_[i][j] = 'Y';
      }
    }
  }

  assert(incoming_restrictions.size() == num_nodes_);
  assert(outgoing_restrictions.size() == num_nodes_);

  for (size_t i = 0; i < num_nodes_; ++i) {
    if (incoming_restrictions[i] == 'N') {
      for (size_t j = 0; j < num_nodes_; ++j) {
        adj_matrix_[j][i] = 'N';
      }
    }

    if (outgoing_restrictions[i] == 'N') {
      for (size_t j = 0; j < num_nodes_; ++j) {
        adj_matrix_[i][j] = 'N';
      }
    }

    adj_matrix_[i][i] = 'Y';
  }
}

const std::vector<std::string> &FlightPlanner::GetPlan() {
  for (size_t i = 0; i < num_nodes_; ++i) {
    for (size_t j = 0; j < num_nodes_; ++j) {
      for (size_t k = 0; k < num_nodes_; ++k) {
        const auto a = adj_matrix_[i][k] == 'Y';
        const auto b = adj_matrix_[k][j] == 'Y';
        auto c = adj_matrix_[i][j] == 'Y';
        c |= a & b;

        adj_matrix_[i][j] = c ? 'Y' : 'N';
      }
    }
  }
  return adj_matrix_;
}
} // namespace fb_qualification_round_2020

int main(int argc, char *argv[]) {
  size_t t{0};
  size_t num_nodes{0};
  std::string input_restrictions;
  std::string output_restrictions;

  std::cin >> t;
  for (size_t case_num = 1; case_num <= t; ++case_num) {
    std::cin >> num_nodes >> input_restrictions >> output_restrictions;
    std::cout << "Case #" << case_num << ':' << std::endl;
    auto flight_planner = fb_qualification_round_2020::FlightPlanner(
        num_nodes, input_restrictions, output_restrictions);
    for (const auto &country_status : flight_planner.GetPlan()) {
      std::cout << country_status << std::endl;
    }
  }
  return 0;
}
