#include <iostream>
#include <print>
#include <vector>

bool check_freshness(uint64_t x, auto& f_ranges) {
  for (auto& [l, r] : f_ranges) {
    if (x >= l && x <= r) return 1;
  }
  return 0;
}

auto collapse_ranges(auto f_ranges) {
  std::vector<std::pair<uint64_t,uint64_t>> g_ranges;

  g_ranges.emplace_back(f_ranges[0]);
  for (auto [l, r] : f_ranges) {
    if (l <= g_ranges.back().second) {
      if (r > g_ranges.back().second)
        g_ranges.back().second = r;
    } else {
      g_ranges.emplace_back(std::make_pair(l,r));
    }
  }

  return g_ranges;
}

int main() {
  std::string line;
  std::vector<std::pair<uint64_t,uint64_t>> f_ranges;
  std::vector<uint64_t> ingredients;

  int silver = 0;
  while (std::cin.peek() != '\n') {
    std::getline(std::cin, line);
    f_ranges.emplace_back(std::make_pair(
      std::stoull(line.substr(0,line.find('-'))),
      std::stoull(line.substr(line.find('-')+1))
    ));
  }
  
  int64_t in;
  while (std::cin >> in) {
    ingredients.emplace_back(in);
  }

  std::sort(f_ranges.begin(), f_ranges.end(), 
            [](auto x, auto y){
            return x.first < y.first;
  });

  auto g_ranges = collapse_ranges(f_ranges);

  for (auto& x : ingredients) {
    silver += check_freshness(x, g_ranges);
  }

  uint64_t gold = 0;
  for (auto [l, r] : g_ranges) {
    if (l != 0)
    gold += (r - l) + 1;
  }

  std::println("Silver: {}", silver);
  std::println("Gold: {}", gold);
}
