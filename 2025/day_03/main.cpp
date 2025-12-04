#include <iostream>
#include <print>
#include <array>

uint64_t check_line(std::string line, int bats=2) {
  int c_max_pos = 0;
  std::array<int,12> res = {};
  int chars_left = bats;
  while (chars_left>0) {
    int t_max_pos = c_max_pos;
    for (int i = c_max_pos + 1; i < line.size() - chars_left + 1; i++) {
      if (line[i] - '0' > res[bats-chars_left]) {
        res[bats-chars_left] = line[i] - '0';
        t_max_pos = i;
      }
    }
    chars_left--;
    c_max_pos = t_max_pos;
  }

  uint64_t ret = 0;
  for (auto x : res) {
    if (x > 0) {
      ret *= 10;
      ret += x;
    }
  }

  return ret;
}

int main() {
  int silver = 0;
  uint64_t gold = 0;

  std::string line;
  while (std::getline(std::cin, line)) {
    silver += check_line(line);
    gold += check_line(line, 12);
  }

  std::println("Silver: {}", silver);
  std::println("Gold: {}", gold);
}
