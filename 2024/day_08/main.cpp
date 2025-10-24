#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>

int solve(auto& antennas, const int map_y, const int map_x, const bool gold = 0) {
  std::set<std::pair<int,int>> antinodes;
  for (auto [_, x] : antennas) {
    for (int i = 0; i < x.size(); i++) {
      const auto [sy, sx] = x[i];
      for (int j = i + 1; j < x.size(); j++) {
        const auto [ey, ex] = x[j];
        const int dy = ey - sy;
        const int dx = ex - sx;

        if (!gold) {
          const int cx1 = sx - dx, cx2 = ex + dx;
          if (sy-dy >= 0 && cx1 < map_x && cx1 >= 0)
            antinodes.insert({sy-dy, cx1});

          if (ey+dy < map_y && cx2 >= 0 && cx2 < map_x)
            antinodes.insert({ey+dy, cx2});
        } else {
          int cx1 = sx, cx2 = ex;
          int cy1 = sy, cy2 = ey;
          while (cy1 >= 0 && cx1 < map_x && cx1 >= 0) {
            antinodes.insert({cy1, cx1});
            cx1 -= dx;
            cy1 -= dy;
          }
          while (cy2 < map_y && cx2 >= 0 && cx2 < map_x) {
            antinodes.insert({cy2, cx2});
            cx2 += dx;
            cy2 += dy;
          }
        }
      }
    }
  }
  return antinodes.size();
}

int main() {
  std::string line;
  auto map = new std::vector<std::string>{};
  //std::vector<std::string> map;
  while (std::getline(std::cin, line))
    (*map).push_back(line);

  const int map_y = (*map).size();
  const int map_x = (*map)[0].size();

  std::unordered_map<char,std::vector<std::pair<int,int>>> antennas;

  for (int i = 0; i < map_y; i++)
    for (int j = 0; j < map_x; j++)
      if ((*map)[i][j] != '.')
        antennas[(*map)[i][j]].push_back({i,j});
  delete map;

  std::cout<<"Silver: "<<solve(antennas,map_y,map_x,0)<<std::endl;
  std::cout<<"Gold: "<<solve(antennas,map_y,map_x,1)<<std::endl;
}
