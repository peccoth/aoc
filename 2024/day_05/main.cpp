#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <sstream>
#include <unordered_map>


int main() {
  std::vector<std::vector<int>> updates;
  updates.reserve(100);
  std::string line, temp;
  unsigned long t1, t2, silver = 0, gold = 0;

  std::unordered_map<int, std::set<int>> rules;
  while (std::cin.peek() != '\n') {
    std::getline(std::cin, temp, '|');
    t1 = std::stoi(temp);
    std::getline(std::cin, temp);
    t2 = std::stoi(temp);
    rules[t2].insert(t1);
  }

  while (std::getline(std::cin, line)) {
    std::stringstream ss(line);
    std::vector<int> update;
    while (std::getline(ss,temp,',')) {
      update.push_back(std::stoi(temp));
    }
    if (update.size() > 0)
      updates.push_back(update);
  }

  const auto cmp = [&rules](int a, int b) {
    return rules[b].contains(a);
  };

  for (std::vector<int>& update : updates) {
    auto g = update;
    std::sort(g.begin(), g.end(), cmp);
    if (g == update)
      silver += update[update.size()/2];
    else {
      gold += g[g.size()/2];
    }
  }
  std::cout<<silver<<std::endl;
  std::cout<<gold<<std::endl;
}
