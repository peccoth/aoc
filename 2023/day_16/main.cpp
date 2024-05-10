#include <iostream>
#include <vector>
#include <stack>
#include <set>

typedef std::vector<std::string> grid_t;
typedef std::vector<std::vector<int>> counter_grid_t;

enum { D, N, E, S, W };
struct laser {
  int i;
  int j;
  int d;
};

int laser_path(grid_t& input, counter_grid_t visited, int si = 0, int sj = 0, int sd = E) {
  std::stack<laser> lasers;
  lasers.push({si, sj, sd});
  while (lasers.size() > 0) {
    auto [i, j, d] = lasers.top();
    lasers.pop();

    if (i < 0)
      d = D;
    if (j < 0)
      d = D;
    if (i > input.size() - 1)
      d = D;
    if (j > input.back().size() - 1)
      d = D;

    if (d != D && ((visited[i][j] & (1 << d)) == (1 << d))) {
      d = D;
      continue;
    }

    if (d == D)
      continue;

    visited[i][j] |= (1 << d);

    if (input[i][j] == '\\') {
      switch (d) {
        case N:
          d = W;
          break;
        case E:
          d = S;
          break;
        case S:
          d = E;
          break;
        case W:
          d = N;
          break;
      }
    }

    if (input[i][j] == '/') {
      switch (d) {
        case N:
          d = E;
          break;
        case E:
          d = N;
          break;
        case S:
          d = W;
          break;
        case W:
          d = S;
          break;
      }
    }

    if (input[i][j] == '-') {
      if (d == N || d == S) {
        d = E;
        lasers.push({i, j - 1, W});
      } 
    } else {
      if (input[i][j] == '|' ) {
        if (d == E || d == W) {
          d = S;
          lasers.push({i - 1, j, N});
        }
      }
    }

    switch (d) {
      case N:
        lasers.push({i - 1, j, d});
        break;
      case E:
        lasers.push({i, j + 1, d});
        break;
      case S:
        lasers.push({i + 1, j, d});
        break;
      case W:
        lasers.push({i, j - 1, d});
        break;
    }

  }

  int result = 0;
  for (auto x : visited) {
    for (auto c : x) {
      result += c > 0;
    }
  }
  return result;
}

int main() {
  std::string line;
  grid_t input;
  counter_grid_t visited;

  while (std::getline(std::cin,line)) {
    input.push_back(line);
  }
  for (int i = 0; i < input.size(); i++) {
    std::vector<int> temp;
    for (int j = 0; j < input[0].size(); j++)
      temp.push_back(0);

    visited.push_back(temp);
  }

  int silver = laser_path(input, visited);

  int gold = 0;
  for (int i = 0; i < input[0].size(); i++) {
    if (i == 0) {
      int a1 = laser_path(input, visited, 0, i, E);
      gold = gold > a1 ? gold : a1;
    }
    if (i == input[0].size()-1) {
      int a1 = laser_path(input, visited, 0, i, E);
      gold = gold > a1 ? gold : a1;
    }
    int a2 = laser_path(input, visited, 0, i, S);
    gold = gold > a2 ? gold : a2;
  }

  for (int i = 0; i < input[0].size(); i++) {
    if (i == 0) {
      int a1 = laser_path(input, visited, 0, i, E);
      gold = gold > a1 ? gold : a1;
    }
    if (i == input[0].size()-1) {
      int a1 = laser_path(input, visited, 0, i, E);
      gold = gold > a1 ? gold : a1;
    }
    int a2 = laser_path(input, visited, 0, i, N);
    gold = gold > a2 ? gold : a2;
  }
  for (int i = 1; i < input.size() - 1; i++) {
    int a2 = laser_path(input, visited, i, 0, E);
    gold = gold > a2 ? gold : a2;
  }
  for (int i = 1; i < input.size() - 1; i++) {
    int a2 = laser_path(input, visited, i, input[0].size() - 1, W);
    gold = gold > a2 ? gold : a2;
  }

  std::cout<<"Silver: "<<silver<<"\n";
  std::cout<<"Gold: "<<gold<<"\n";
}
