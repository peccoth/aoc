#include <iostream>
#include <vector>
#include <set>

typedef std::tuple<int,int,int> Position;

const std::pair<int,int> directions[] = {
  {-1,0}, {0,1}, {1,0}, {0,-1}
};

bool brute_force(auto& map, Position pos) {
  auto [y, x, dir] = pos;
  std::set<Position> visited;

  while (x > 0 && x < map[0].size() - 1 && 
         y > 0 && y < map.size() - 1) {
    x++;
    std::cout<<x<<std::endl;

    if (visited.contains(pos))
      return 1;
    visited.insert(pos);

    const int ny = y + directions[dir].first;
    const int nx = x + directions[dir].second;
    if (map[ny][nx] == '#')
        dir = (dir + 1) % 4;

    y = ny;
    x = nx;
  }
  return 0;
}

int main() {
  std::vector<std::string> map;
  std::string line;

  while(std::getline(std::cin,line)) {
    map.push_back(line);
  }

  Position pos;
  for (int i = 0; i < map.size(); i++) 
    for (int j = 0; j < map[0].size(); j++)
      if (map[i][j] == '^') {
        pos = {i, j, 0};
        goto found;
      }

found:
  Position start_pos = pos;

  std::set<std::pair<int,int>> visited;
  auto [y, x, dir] = pos;
  while (x > 0 && x < map[0].size() - 1 && 
         y > 0 && y < map.size() - 1) {

    const int ny = y + directions[dir].first;
    const int nx = x + directions[dir].second;
    if (map[ny][nx] == '#')
        dir = (dir + 1) % 4;
   
    y += directions[dir].first;
    x += directions[dir].second;
    visited.insert({y, x});
  }
  std::cout<<"Silver: "<<visited.size()<<std::endl;

  int gold = 0;
  const auto [sy, sx, _] = start_pos;
  for (auto [cy, cx] : visited) {
    if (cy == sy && cx == sx) continue;
    auto n_map = map;
    n_map[cy][cx] = '#';
    const bool gold_s = brute_force(n_map, start_pos);
    gold += gold_s;
  }
  std::cout<<"Gold: "<<gold<<std::endl;
}
