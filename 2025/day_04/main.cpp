#include <iostream>
#include <print>
#include <vector>
#include <unordered_set>


template<class A, class B>
struct std::hash<std::pair<A, B>> {
    size_t operator()(std::pair<A,B> const& p) const noexcept {
        size_t h1 = std::hash<A>{}(p.first);
        size_t h2 = std::hash<B>{}(p.second);
        // 64-bit mix; anything sane is fine
        return h1 ^ (h2 + 0x9e3779b97f4a7c15ULL + (h1 << 6) + (h1 >> 2));
    }
};

bool look_around(int i, int j, std::vector<std::string>& map) {
  int roll_count = 0;

  if (i > 0) {
    if (j > 0) {
      roll_count += map[i-1][j-1] == '@';
    }
    if (j < map.size()-1) {
      roll_count += map[i-1][j+1] == '@';
    }
    roll_count += map[i-1][j] == '@';
  }

  if (i < map[0].size()-1) {
    if (j > 0) {
      roll_count += map[i+1][j-1] == '@';
    }
    if (j < map.size()-1) {
      roll_count += map[i+1][j+1] == '@';
    }
    roll_count += map[i+1][j] == '@';
  }

  if (j > 0) {
    roll_count += map[i][j-1] == '@';
  }

  if (j < map.size()-1) {
    roll_count += map[i][j+1] == '@';
  }

  return roll_count < 4;
}

int gold_iteration(auto& map) {
  std::unordered_set<std::pair<int,int>> removable = {};

  for (int i = 0; i < map.size(); i++) {
    for (int j = 0; j < map[0].size(); j++) {
      if (map[i][j] == '@') {
        if (look_around(i, j, map)) {
          removable.insert({i,j});
        }
      }
    }
  }

  if (removable.size() > 0) {
    for (auto [i, j] : removable) {
      map[i][j] = '.';
    }
  }

  return removable.size();
}

int main() {
  std::vector<std::string> map;
  std::string line;
  int silver = 0;
  int gold = 0;

  while (std::getline(std::cin, line)){
    map.emplace_back(line);
  }

  for (int i = 0; i < map.size(); i++) {
    for (int j = 0; j < map[0].size(); j++) {
      if (map[i][j] == '@') {
        silver += look_around(i, j, map);
      }
    }
  }

  int it = silver;
  while (it != 0) {
    it = gold_iteration(map);
    gold += it;
  }


  std::println("Silver: {}", silver);
  std::println("Gold: {}", gold);

}
