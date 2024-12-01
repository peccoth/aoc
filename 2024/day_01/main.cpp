#include <algorithm>
#include <cstdint>
#include <iostream>
#include <sstream>
#include <vector>

int main() {
  int a;
  std::vector<int> locations_l;
  std::vector<int> locations_r;
  int occurances[100000] = {0};

  std::string line;
  while (std::getline(std::cin, line)) {
    std::istringstream iss(line);
    iss >> a;
    locations_l.push_back(a);
    iss >> a;
    locations_r.push_back(a);
    occurances[a]++;
  }

  std::sort(locations_l.begin(), locations_l.end());
  std::sort(locations_r.begin(), locations_r.end());

  int silver = 0;
  for (int i =0; i < locations_l.size(); i++) {
    int value = locations_l[i] - locations_r[i];
    uint32_t temp = value >> 31;
    value ^= temp;
    value += temp & 1;
    silver += value;
  }

  int gold = 0;
  for (auto x : locations_l) {
    gold += x * occurances[x];
  }

  std::cout<<silver<<std::endl;
  std::cout<<gold<<std::endl;
}
