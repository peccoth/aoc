#include <climits>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <vector>

enum {NORTH, EAST, SOUTH, WEST};
typedef std::tuple<int,int,int> pos;

auto main() -> int {
  auto maze = std::vector<std::string>{};
  std::string line;
  while (std::getline(std::cin, line)) {
    maze.push_back(line);
  }

  pos start;
  std::pair<int,int> finish;
  for (int i = 0; i < maze.size(); i++) {
    for (int j = 0; j < maze[0].size(); j++) {
      if (maze[i][j] == 'S') start = {i, j, EAST};
      if (maze[i][j] == 'E') finish = {i, j};
    }
  }

  const std::pair<int,int> directions[] = {{-1, 0},{0, 1},{1,0}, {0,-1}};
  auto visited = std::map<pos, int>{};
  visited[{start}] = 0;
  auto queue = std::queue<pos>{};
  queue.push(start);
  while (!queue.empty()) {
    auto [y, x, d] = queue.front();
    queue.pop();

    const int lr = (d == NORTH) * 1000 + (d == SOUTH) * 1000 + 1;
    const int tb = (d == EAST) * 1000 + (d == WEST) * 1000 + 1;

    if (maze[y-1][x] != '#' && d != SOUTH) {
      pos npos = {y-1, x, NORTH};
      if (visited.find(npos) == visited.end() || 
          visited[{y,x,d}] + tb < visited[npos] ) 
      {
        visited[npos] = visited[{y,x,d}] + tb;
        queue.push(npos);
      }
    }
    if (maze[y+1][x] != '#' && d != NORTH) {
      pos npos = {y+1, x, SOUTH};
      if (visited.find(npos) == visited.end() || 
          visited[{y,x,d}] + tb < visited[npos]) 
      {
        visited[npos] = visited[{y,x,d}] + tb;
        queue.push(npos);
      }
    }
    if (maze[y][x - 1] != '#' && d != WEST) {
      pos npos = {y, x - 1, EAST};
      if (visited.find(npos) == visited.end() || 
          visited[npos] > visited[{y,x,d}] + lr) 
      {
        visited[npos] = visited[{y,x,d}] + lr;
        queue.push(npos);
      }
    }

    if (maze[y][x + 1] != '#' && d != EAST) {
      pos npos = {y, x + 1, WEST};
      if (visited.find(npos) == visited.end() || 
          visited[npos] > visited[{y,x,d}] + lr) 
      {
        visited[npos] = visited[{y,x,d}] + lr;
        queue.push(npos);
      }
    }
  }
  int silver = INT_MAX;
  for (int i = 0; i < 4; i++) {
    if (visited[{finish.first, finish.second, i}] > 0) {
      silver = std::min(visited[{finish.first, finish.second, i}], silver);
      start = {finish.first, finish.second, i};
    }
  }
  std::cout<<silver<<std::endl;
  
  queue.push(start);
  auto tiles = std::set<std::pair<int,int>>{};

  auto [y, x, d] = queue.front();
  for (int j = 0; j < 4; j++) {
    auto [ll, rr] = directions[j];
    for (int i = 0; i < 4; i++) {
      if (visited[{y + ll,x + rr,i}] < silver
          && visited[{y + ll, x + rr, i}] > 0) 
      {
        tiles.insert({y + ll,x + rr});
        queue.push({y + ll,x + rr,i});
      }
    }
  }
  queue.pop();

  int dead=0;
  while (!queue.empty()) {
    auto cpos = queue.front();
    auto [y, x, d] = cpos;
    queue.pop();

    for (int j = 0; j < 4; j++) {
      auto [ll, rr] = directions[j];
      for (int i = 0; i < 4; i++) {
        if (visited[{y + ll,x + rr,i}] < visited[cpos] 
            && visited[{y + ll, x + rr, i}] > 0
            ) {
          tiles.insert({y + ll,x + rr});
          queue.push({y + ll,x + rr,i});
        }
      }
    }
  }
  int arr[141][141]{};
  for (auto x : tiles) {
    arr[x.first][x.second] = 1;
  }
  for (int i = 0; i < 141; i++) {
    for (int j = 0; j < 141; j++) {
      std::cout<<arr[i][j];
    }
    std::cout<<std::endl;
  }

  std::cout<<tiles.size() + 2<<std::endl;
  std::cout<<dead<<std::endl;
}
