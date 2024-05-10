#include <iostream>
#include <vector>
#include <sstream>
#include <limits>

struct triple {
  unsigned long long first;
  unsigned long long second;
  unsigned long long third;
};
std::vector<triple> get_stage() {
  std::string line;
  std::getline(std::cin, line);

  triple temp;
  std::vector<triple> out;

  while (std::getline(std::cin, line)) {
    if (line[0] == '\0')
      break;

    std::stringstream ss(line);
    ss >> temp.first;
    ss >> temp.second;
    ss >> temp.third;
    out.push_back(temp);
  }
  return out;
}

auto process_seed(unsigned long long seed, auto& stages) {
  for (auto& stage : stages)
  for (auto& [first, second, third]: stage) 
    if (seed >= second && seed < second + third ) {
      seed = first + (seed - second);
      break;
    }
  return seed;
}

int main() {
  std::string line, trash;
  unsigned long long temp;
  std::getline(std::cin, line);
  std::stringstream ss(line);

  std::vector<unsigned long long> seeds;
  std::vector<std::pair<unsigned long long, unsigned long long>> gold_seed_ranges;
  ss >> trash;

  while (ss >> temp) 
    seeds.push_back(temp);
  
  for (int i = 0; i < seeds.size(); i+=2)
    gold_seed_ranges.push_back({seeds[i], seeds[i+1]});

  std::vector<std::vector<triple>> stages;
  std::getline(std::cin, line);
  for (int i = 0; i < 7; ++i) {
    std::vector<triple> stage = get_stage();
    stages.push_back(stage);
  }

  unsigned long long gold = INT64_MAX;

  int counter = 0;
  for (auto& x : gold_seed_ranges) {
    for (unsigned long long i=0; i < x.second; i++) {
      counter ++;
      temp = process_seed(x.first + i, stages);
      gold = temp < gold ? temp : gold;
    }
  }

  unsigned long long silver = std::numeric_limits<unsigned long>::max();
  for (auto x : seeds) {
    temp = process_seed(x, stages);
    silver = temp < silver ? temp : silver;
  }

  std::cout<<"Silver: "<<silver<<"\n";
  std::cout<<"Gold: "<<gold<<"\n";
}
