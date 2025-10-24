#include <iostream>
#include <set>
#include <vector>
#include <iterator>
#include <map>
#include <queue>

struct walls {
  bool left;
  bool right;
  bool down;
  bool up;
};

int silver (auto& map) {
  std::set<std::pair<int,int>> visited;
  int i = 0, j=0;
  long silver = 0;
  while (visited.size() < map.size() * map[0].size()) {
    std::queue<std::pair<int,int>> flood;
    flood.push({j,i});
    char curr = map[j][i];
    int c_walls = 0;
    int c_size_start = visited.size();
    while (flood.size()) {
      auto [y, x] = flood.front();
      flood.pop();
      if (visited.contains({y,x})) continue;;
      visited.insert({y,x});
      if (y > 0 && map[y-1][x] == curr) { //up
        flood.push({y-1,x});
      } else c_walls++;
      if (x > 0 && map[y][x-1] == curr) { //left
        flood.push({y,x-1});
      } else c_walls++;
      if (y < map.size() - 1 && map[y+1][x] == curr) { //down
        flood.push({y+1,x});
      } else c_walls++;
      if (x < map[0].size() - 1 && map[y][x+1] == curr) { //right
        flood.push({y,x + 1});
      } else c_walls++;
    }
    i++;
    silver += (visited.size() - c_size_start) * c_walls;
    if (i > map[0].size() - 1) {
      i = 0;
      j++;
    }
    if (j > map.size() - 1) break;
  }
  return silver;
}

int gold(auto& map) {
  std::set<std::pair<int,int>> visited;
  int i = 0, j=0;
  while (visited.size() < map.size() * map[0].size()) {
    std::queue<std::pair<int,int>> flood;
    flood.push({j,i});
    char curr = map[j][i];
    int c_size_start = visited.size();
    std::map<std::pair<int,int>, walls> sub_visited;
    while (flood.size()) {
      walls c{};
      auto [y, x] = flood.front();
      flood.pop();
      if (visited.contains({y,x})) continue;;
      visited.insert({y,x});
      if (y > 0 && map[y-1][x] == curr) { //up
        flood.push({y-1,x});
        c.up = 0;
      } else c.up = 1;
      if (x > 0 && map[y][x-1] == curr) { //left
        flood.push({y,x-1});
        c.left = 0;
      } else c.left = 1;
      if (y < map.size() - 1 && map[y+1][x] == curr) { //down
        flood.push({y+1,x});
        c.down = 0;
      } else c.down = 1;
      if (x < map[0].size() - 1 && map[y][x+1] == curr) { //right
        flood.push({y,x + 1});
        c.right = 0;
      } else c.right = 1;
      sub_visited[{y, x}] = c;
    }
    i++;
    if (i > map[0].size() - 1) {
      i = 0;
      j++;
    }

    int walls = 0;
    for (auto [l, r] : sub_visited) {
      if (r.up && r.right) walls++;
      if (r.up && r.left) walls++;
      if (r.down && r.left) walls++;
      if (r.down && r.right) walls++;
    }
    if (j > map.size() - 1) break;
    std::cout<<walls<<std::endl;
  }
  return 0;
}

int main() {
  std::vector<std::string> map{std::istream_iterator<std::string>(std::cin), 
                               std::istream_iterator<std::string>()};

  std::cout<<"Silver: "<<silver(map)<<std::endl;
  std::cout<<"Gold: "<<gold(map)<<std::endl;
}
