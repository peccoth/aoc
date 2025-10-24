#include <iostream>
#include <sstream>
#include <vector>

enum {
  ASC, DESC
};
bool check_two(bool dir, int curr, int prev) {
  bool res = 1;
  switch (dir) {
    case ASC:
      if (curr <= prev || curr - prev > 3)
        res = 0;
      break;
    case DESC:
      if (curr >= prev || prev - curr > 3)
        res = 0;
      break;
  }
  return res;
}
bool check_silver(std::vector<int>& line, int skip = -1) {
  bool dir = ASC;
  int curr = 1;
  if (line[curr - 1] > line[curr])
    dir = DESC;

  if (!check_two(dir,line[curr],line[curr-1]))
    return 0;

  for (;curr < line.size(); curr++) {
    if (curr == skip) 
      continue;
    if (!check_two(dir,line[curr],line[curr-1]))
      return 0;
  }
  return 1;
}

bool check_gold(std::vector<int>& line) {
  bool ret = 0;
  for (int i = 0; i < line.size(); i++) {
    if (check_silver(line, i)) {
      ret = 1;
      break;
    }
  }
  return ret;
}

int main() {
  int silver = 0, gold = 0;
  std::string line;
  int i = 0;

  while (std::getline(std::cin, line)) {
    std::vector<int> arr = {};
    int tmp;
    std::stringstream ss(line);
    while ( ss >> tmp) {
      arr.push_back(tmp);
    }
    std::cout<<++i<<std::endl;
    silver += check_silver(arr);
    gold += check_gold(arr);
  }
  std::cout<<silver<<std::endl;
  std::cout<<gold<<std::endl;
}
