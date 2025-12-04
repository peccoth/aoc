#include <iostream>
#include <print>

int main() {
  int p = 50;
  int silver = 0, gold = 0;
  std::string line;
  while (std::getline(std::cin, line)) {
    int move = stoi(line.substr(1)) * (line[0] == 'R' ? 1 : -1);
    std::println("Current position: {}", p);
    std::println("Move: {}", move);
    std::println("Gold: {}\n", gold);
    
    if (p == 0) {
      gold += abs(move) / 100;
      move %= 100;
    } else {
      gold += abs(move) / 100;
      move %= 100;
      gold += ((p + move) < 0) + ((p + move) > 100);
    }

    p += move;
    p %= 100;
    if (p < 0)
      p = 100 + p;

    silver += p == 0;
  }

  std::println("Silver: {}\n", silver);
  std::println("Gold: {}\n", gold);
}
