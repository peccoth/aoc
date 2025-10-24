#include <iostream>
#include <cmath>
#include <regex>

int main() {
  std::string line;
  std::string temp;
  std::regex regex(R"(\bX\+(\d+), Y\+(\d+))");
  std::regex regex2(R"(\bX=(\d+), Y=(\d+))");
  int64_t silver = 0;
  int64_t gold = 0;
  while (std::cin.peek() != EOF) {
    std::smatch match;
    std::getline(std::cin, line);
    std::regex_search(line, match, regex);
    const auto [ax, ay] = std::pair{std::stoi(match[1].str()), std::stoi(match[2].str())};

    std::getline(std::cin, line);
    std::regex_search(line, match, regex);
    const auto [bx, by] = std::pair{std::stoi(match[1].str()), std::stoi(match[2].str())};
    
    std::getline(std::cin, line);
    std::regex_search(line, match, regex2);
    const auto [x, y] = std::pair{std::stoi(match[1].str()), std::stoi(match[2].str())};
    std::getline(std::cin, line);

    const int64_t res_a = (y*bx - x * by) / (ay * bx - ax * by);
    const int64_t res_b = (y*ax - x * ay) / (by * ax - bx * ay);
    if (res_a * ax + res_b * bx == x && 
        res_a * ay + res_b * by == y) 
    {
      silver += res_a * 3 + res_b;
    }

    const int64_t gy = y + 10000000000000ULL;
    const int64_t gx = x + 10000000000000ULL;
    const int64_t res_ga = (gy*bx - gx * by) / (ay * bx - ax * by);
    const int64_t res_gb = (gy*ax - gx * ay) / (by * ax - bx * ay);
    if (res_ga * ax + res_gb * bx == gx && 
        res_ga * ay + res_gb * by == gy) 
    {
      gold += res_ga * 3 + res_gb;
    }

  }
  std::cout<<silver<<std::endl;
  std::cout<<gold<<std::endl;
}
