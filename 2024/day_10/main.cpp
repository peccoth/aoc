#include <iostream>
#include <set>
#include <vector>
#include <queue>

int main() {
  int silver = 0, gold = 0;
  std::string line;
  std::vector<std::vector<int>> topography;
  std::queue<std::pair<int,int>> trails;

  while (std::getline(std::cin, line)) {
    std::vector<int> temp{};
    for (auto x : line) temp.push_back(x - '0');
    topography.push_back(temp);
  }

  for (int i = 0; i < topography.size(); i++)
    for (int j = 0; j < topography[0].size(); j++)
      if (topography[i][j] == 0)
        trails.push({i, j});

  while (!trails.empty()) {
    auto [l, r] = trails.front();
    std::queue<std::pair<int,int>> trail{};
    std::set<std::pair<int,int>> reached;

    trails.pop();
    trail.push({l,r});
    int score = 0;
    while (!trail.empty()) {
      auto [y, x] = trail.front();
      trail.pop();

      if (topography[y][x] == 9) {
        reached.insert({y,x});
        score++;
        continue;
      } 
      
      if ((y < (topography.size() - 1)) && 
          ((topography[y][x] + 1) == topography[y+1][x]))
        trail.push({y+1,x});
      if ((x < (topography[0].size() - 1)) && 
          ((topography[y][x] + 1) == topography[y][x+1]))
        trail.push({y,x+1});
      if ((y > 0) && 
          ((topography[y][x] + 1) == topography[y-1][x]))
        trail.push({y-1,x});
      if ((x > 0) && 
          ((topography[y][x] + 1) == topography[y][x-1]))
        trail.push({y,x-1});
    }
    
    silver += reached.size();
    gold += score;
  }
  std::cout<<silver<<std::endl;
  std::cout<<gold<<std::endl;
}
