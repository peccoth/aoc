#include <iostream>
#include <vector>
#include <sstream>

typedef std::pair<int, int> pos;

int silver (auto& warehouse, auto& line) {
  pos robot;
  for (int i = 0; i < warehouse.size(); i++) {
    for (int j = 0; j < warehouse[0].size();j++) {
      if (warehouse[i][j] == '@')
          robot = {i, j};
    }
  }

  for (auto x : line) {
    int first_dot = -1;
    switch (x) {
      case '^':
        for (int i = robot.first; i >= 0; i--) {
          if (warehouse[i][robot.second] == '.') {first_dot = i; break;}
          if (warehouse[i][robot.second] == '#') {break;}
        }
        if (first_dot > -1) {
          if (robot.first - first_dot == 1) {
            warehouse[robot.first][robot.second] = '.';
            warehouse[first_dot][robot.second] = '@';
            robot.first = first_dot;
          } else {
            warehouse[first_dot][robot.second] = 'O';
            warehouse[robot.first--][robot.second] = '.';
            warehouse[robot.first][robot.second] = '@';
          }
        }
      break;
      case '>':
        for (int i = robot.second; i < warehouse[0].size(); i++) {
          if (warehouse[robot.first][i] == '.') {first_dot = i; break;}
          if (warehouse[robot.first][i] == '#') {break;}
        }
        if (first_dot > -1) {
          if (first_dot - robot.second == 1) {
            warehouse[robot.first][robot.second] = '.';
            warehouse[robot.first][first_dot] = '@';
            robot.second = first_dot;
          } else {
            warehouse[robot.first][first_dot] = 'O';
            warehouse[robot.first][robot.second++] = '.';
            warehouse[robot.first][robot.second] = '@';
          }
        }
      break;
      case '<':
        for (int i = robot.second; i >= 0; i--) {
          if (warehouse[robot.first][i] == '.')  {first_dot = i; break;}
          if (warehouse[robot.first][i] == '#')  {break;}
        }
        if (first_dot > -1) {
          if (robot.second - first_dot == 1) {
            warehouse[robot.first][robot.second] = '.';
            warehouse[robot.first][first_dot] = '@';
            robot.second = first_dot;
          } else {
            warehouse[robot.first][first_dot] = 'O';
            warehouse[robot.first][robot.second--] = '.';
            warehouse[robot.first][robot.second] = '@';
          }
        }
      break;
      case 'v':
        for (int i = robot.first; i < warehouse.size(); i++) {
          if (warehouse[i][robot.second] == '.') {first_dot = i; break;}
          if (warehouse[i][robot.second] == '#') {break;}
        }
        if (first_dot > -1) {
          if (first_dot - robot.first == 1) {
            warehouse[robot.first][robot.second] = '.';
            warehouse[first_dot][robot.second] = '@';
            robot.first = first_dot;
          } else {
            warehouse[first_dot][robot.second] = 'O';
            warehouse[robot.first++][robot.second] = '.';
            warehouse[robot.first][robot.second] = '@';
          }
        }
      break;
    }

    if (first_dot == -1) continue;
  }
  long silver = 0;
  for (int i = 0; i < warehouse.size(); i++) {
    for (int j = 0; j < warehouse[0].size();j++) {
      if (warehouse[i][j] == 'O')
        silver+=i*100 + j;
    }
  }
  return silver;
}

bool check(auto& warehouse, pos p) {
  if (warehouse[p.first][p.second] == '#')
    return 1;
  if (warehouse[p.first][p.second] == '.')
    return 0;

  if (warehouse[p.first][p.second] == ']')
    return check(warehouse,{p.first-1, p.second}) + check(warehouse, {p.first-1, p.second-1});
  return check(warehouse,{p.first-1, p.second}) + check(warehouse, {p.first-1, p.second+1});
}

bool check_down(auto& warehouse, pos p) {
  if (warehouse[p.first][p.second] == '#')
    return 1;
  if (warehouse[p.first][p.second] == '.')
    return 0;

  if (warehouse[p.first][p.second] == ']')
    return check_down(warehouse,{p.first+1, p.second}) + check_down(warehouse, {p.first+1, p.second-1});
  return check_down(warehouse,{p.first+1, p.second}) + check_down(warehouse, {p.first+1, p.second+1});
}

void move_up(auto& warehouse, pos p) {

  if (warehouse[p.first][p.second] == '.') return;
  if (warehouse[p.first][p.second] == ']') {
    if (warehouse[p.first-1][p.second] == '.' && warehouse[p.first-1][p.second-1] == '.') {
      warehouse[p.first-1][p.second] = warehouse[p.first][p.second];
      warehouse[p.first-1][p.second-1] = warehouse[p.first][p.second-1];
      warehouse[p.first][p.second] = '.';
      warehouse[p.first][p.second-1] = '.';
      return;
    } else {
    move_up(warehouse, {p.first-1, p.second});
    move_up(warehouse, {p.first-1, p.second-1});
    }
  } else if (warehouse[p.first][p.second] == '[') {
    if (warehouse[p.first-1][p.second] == '.' && warehouse[p.first-1][p.second+1] == '.') {
      warehouse[p.first-1][p.second] = warehouse[p.first][p.second];
      warehouse[p.first-1][p.second+1] = warehouse[p.first][p.second+1];
      warehouse[p.first][p.second] = '.';
      warehouse[p.first][p.second+1] = '.';
      return;
    } else {
    move_up(warehouse, {p.first-1, p.second});
    move_up(warehouse, {p.first-1, p.second+1});
    }
  }

  if (warehouse[p.first][p.second] == '[') {
    warehouse[p.first-1][p.second] = warehouse[p.first][p.second];
    warehouse[p.first-1][p.second+1] = warehouse[p.first][p.second+1];
    warehouse[p.first][p.second] = '.';
    warehouse[p.first][p.second+1] = '.';
  }
  if (warehouse[p.first][p.second] == ']') {
    warehouse[p.first-1][p.second] = warehouse[p.first][p.second];
    warehouse[p.first-1][p.second-1] = warehouse[p.first][p.second-1];
    warehouse[p.first][p.second] = '.';
    warehouse[p.first][p.second-1] = '.';
  }
}

void move_down(auto& warehouse, pos p) {
  if (warehouse[p.first][p.second] == '.') return;
  if (warehouse[p.first][p.second] == ']') {
    if (warehouse[p.first+1][p.second] == '.' && warehouse[p.first+1][p.second-1] == '.') {
      warehouse[p.first+1][p.second] = warehouse[p.first][p.second];
      warehouse[p.first+1][p.second-1] = warehouse[p.first][p.second-1];
      warehouse[p.first][p.second] = '.';
      warehouse[p.first][p.second-1] = '.';
      return;
    } else {
    move_down(warehouse, {p.first+1, p.second});
    move_down(warehouse, {p.first+1, p.second-1});
    }
  } else if (warehouse[p.first][p.second] == '[') {
    if (warehouse[p.first+1][p.second] == '.' && warehouse[p.first+1][p.second+1] == '.') {
      warehouse[p.first+1][p.second] = warehouse[p.first][p.second];
      warehouse[p.first+1][p.second+1] = warehouse[p.first][p.second+1];
      warehouse[p.first][p.second] = '.';
      warehouse[p.first][p.second+1] = '.';
      return;
    } else {
    move_down(warehouse, {p.first+1, p.second});
    move_down(warehouse, {p.first+1, p.second+1});
    }
  }

  if (warehouse[p.first][p.second] == '[') {
    warehouse[p.first+1][p.second] = warehouse[p.first][p.second];
    warehouse[p.first+1][p.second+1] = warehouse[p.first][p.second+1];
    warehouse[p.first][p.second] = '.';
    warehouse[p.first][p.second+1] = '.';
  }
  if (warehouse[p.first][p.second] == ']') {
    warehouse[p.first+1][p.second] = warehouse[p.first][p.second];
    warehouse[p.first+1][p.second-1] = warehouse[p.first][p.second-1];
    warehouse[p.first][p.second] = '.';
    warehouse[p.first][p.second-1] = '.';
  }
}

int gold (auto& warehouse, auto& line) {
  pos robot;
  for (int i = 0; i < warehouse.size(); i++) {
    for (int j = 0; j < warehouse[0].size();j++) {
      if (warehouse[i][j] == '@')
          robot = {i, j};
    }
  }

  for (auto x : line) {
    int first_dot = -1;
    int immovable = 0;
    switch (x) {
      case '^':
        if (warehouse[robot.first - 1][robot.second] == '.') {
          warehouse[robot.first--][robot.second] = '.';
          warehouse[robot.first][robot.second] = '@';

        } else if (warehouse[robot.first-1][robot.second] == ']'){
          immovable = check(warehouse, {robot.first -1, robot.second}) + check(warehouse, {robot.first-1, robot.second - 1});
          if (!immovable) {
            move_up(warehouse, {robot.first -1, robot.second});
            warehouse[robot.first--][robot.second] = '.';
            warehouse[robot.first][robot.second] = '@';
          }

        } else if (warehouse[robot.first-1][robot.second] == '[') {
          immovable = check(warehouse, {robot.first -1, robot.second}) + check(warehouse, {robot.first-1, robot.second + 1});
          if (!immovable){
            move_up(warehouse, {robot.first -1, robot.second});
            warehouse[robot.first--][robot.second] = '.';
            warehouse[robot.first][robot.second] = '@';
          }
        }
      break;

      case 'v':
        if (warehouse[robot.first + 1][robot.second] == '.') {
          warehouse[robot.first++][robot.second] = '.';
          warehouse[robot.first][robot.second] = '@';
        } else if (warehouse[robot.first+1][robot.second] == ']'){
          immovable = check_down(warehouse, {robot.first +1, robot.second}) + check_down(warehouse, {robot.first+1, robot.second - 1});
          if (!immovable) {
            move_down(warehouse, {robot.first +1, robot.second});
            warehouse[robot.first++][robot.second] = '.';
            warehouse[robot.first][robot.second] = '@';
          }

        } else if (warehouse[robot.first+1][robot.second] == '[') {
          immovable = check_down(warehouse, {robot.first +1, robot.second}) + check_down(warehouse, {robot.first+1, robot.second + 1});
          if (!immovable){
            move_down(warehouse, {robot.first +1, robot.second});
            warehouse[robot.first++][robot.second] = '.';
            warehouse[robot.first][robot.second] = '@';
          }
        }
      break;

      case '>':
        if (warehouse[robot.first][robot.second + 1] == '.') {
          warehouse[robot.first][robot.second++] = '.';
          warehouse[robot.first][robot.second] = '@';
        }else if (warehouse[robot.first][robot.second + 1] == '[') {
          for (int i = robot.second; i < warehouse[0].size(); i++) {
            if (warehouse[robot.first][i] == '#') break;
            if (warehouse[robot.first][i] == '.') {
              first_dot = i;
              break;
            }
          }
          if (first_dot > -1) {
            warehouse[robot.first].erase(warehouse[robot.first].begin() + first_dot);
            warehouse[robot.first].insert(robot.second,1, '.');
            robot.second++;
          }
        }
      break;

      case '<':
        if (warehouse[robot.first][robot.second - 1] == '.') {
          warehouse[robot.first][robot.second--] = '.';
          warehouse[robot.first][robot.second] = '@';
        }else if (warehouse[robot.first][robot.second - 1] == ']') {
          for (int i = robot.second; i > 0; i--) {
            if (warehouse[robot.first][i] == '#') break;
            if (warehouse[robot.first][i] == '.') {
              first_dot = i;
              break;
            }
          }
          if (first_dot > -1) {
            warehouse[robot.first].erase(warehouse[robot.first].begin() + first_dot);
            warehouse[robot.first].insert(robot.second,1, '.');
            robot.second--;
          }
        }
      break;
    }
  }

  long gold = 0;
  for (int i = 0; i < warehouse.size(); i++) {
    for (int j = 0; j < warehouse[0].size();j++) {
      if (warehouse[i][j] == '[')
        gold+=i*100 + j;
    }
  }
  return gold;
}

auto main() -> int {
  std::string line;
  std::vector<std::string> warehouse;
  std::vector<std::string> warehouse2;
  while (std::cin.peek() != '\n') {
    std::getline(std::cin,line);
    warehouse.push_back(line);
  }

  for (const auto& x : warehouse) {
    std::string new_line;
    for (auto y : x) {
      switch (y) {
        case '.':
          new_line += "..";
          break;
        case '#':
          new_line += "##";
          break;
        case 'O':
          new_line += "[]";
          break;
        case '@':
          new_line += "@.";
          break;
      }
    }
    warehouse2.push_back(new_line);
  }

  std::ostringstream oss;
  oss << std::cin.rdbuf();
  line = oss.str();

  std::cout<<silver(warehouse, line)<<std::endl;
  std::cout<<gold(warehouse2, line)<<std::endl;
}
