#include <iostream>
#include <print>
#include <sstream>
#include <vector>

std::vector<std::string> rotated( std::vector<std::string> in) {
  std::vector<std::string> res;
  for (int i = in[0].size(); i >= 0; i--) {
    std::string line;
    for (int j = 0; j < in.size(); j++) {
      line += in[j][i];
    }
    res.emplace_back(line);
  }

  return res;
}

int main() {
  std::vector<std::vector<int>> numbers;
  std::vector<std::string> lines;
  std::string line;
  while (std::cin.peek() != '*' && std::cin.peek() != '+') {
    std::getline(std::cin, line);
    lines.emplace_back(line);
    std::stringstream ss(line);
    int t;
    std::vector<int> row;
    while (ss >> t) {
      row.emplace_back(t);
    }

    numbers.emplace_back(row);
  }

  uint64_t silver = 0;
  size_t col = 0;
  std::vector<char> ops;
  char op;
  while (std::cin >> op) {
    ops.emplace_back(op);
    uint64_t col_sum = op == '*' ? 1 : 0;
    for (int j = 0; j < numbers.size(); j++) {
      if (op == '*') {
        col_sum*= numbers[j][col];
      } else {
        col_sum+= numbers[j][col];
      }
    }
    col++;
    silver += col_sum;
  }

  std::println("Silver: {}", silver);

  std::reverse(ops.begin(), ops.end());
  auto rot = rotated(lines);
  uint64_t gold = 0;
  uint64_t sub_sum = 0;
  int op_i = -1;
  for (auto x : rot) {
    try {
      int c = std::stoi(x);
      if (ops[op_i] == '*') {
        sub_sum *= c;
      } else {
        sub_sum += c;
      }
    } catch (std::invalid_argument){
      gold += sub_sum;
      op_i ++;
      sub_sum = ops[op_i] == '*' ? 1 : 0;
    }
  }
  gold += sub_sum;

  std::println("Gold: {}", gold);
}
