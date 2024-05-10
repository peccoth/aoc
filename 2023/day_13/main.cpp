#include <iostream>
#include <vector>

std::vector<int> find_vertical(std::vector<std::string> block) {
  std::vector<int> ret;
  for (int i = 0; i < block.back().size() - 1; i++) {
    bool good = 1;
    for (int j = 0; j < block.size(); j++) {
      if (block[j][i] != block[j][i+1])
        good = 0;
    }
    if (good)
      ret.push_back( i + 1 );
  }
  return ret;
}
bool check_reflection_v(std::vector<std::string> block, int id) {
  bool ret = 1;
  for (int distance = 0; id + distance < block.back().size() && id - (distance+1) >= 0; distance++) {
    for (int j = 0; j < block.size(); j++) {
      if (block[j][id + distance] != block[j][id-(distance + 1)])
        ret = 0;
    }
  }
  return ret;
}
std::vector<int> find_horizontal(std::vector<std::string> block) {
  std::vector<int> ret;
  for (int i = 0; i < block.size() - 1; i++) {
    bool good = 1;
    for (int j = 0; j < block.back().size(); j++) {
      if (block[i][j] != block[i+1][j])
        good = 0;
    }
    if (good)
      ret.push_back( i + 1 );
  }
  return ret;
}
bool check_reflection_h(std::vector<std::string> block, int id) {
  bool ret = 1;
  for (int distance = 1; id + distance < block.size() && id - (distance+1) >= 0; distance++) {
    for (int j = 0; j < block.back().size(); j++) {
      if (block[id + distance][j] != block[id-(distance + 1)][j])
        ret = 0;
    }
  }
  return ret;
}

std::vector<std::pair<int,bool>> find_vertical_gold(std::vector<std::string> block) {
  std::vector<std::pair<int,bool>> ret;
  for (int i = 0; i < block.back().size() - 1; i++) {
    int smudge_count = 0;
    for (int j = 0; j < block.size(); j++) {
      if (block[j][i] != block[j][i+1])
        smudge_count++;
    }
    if (smudge_count < 2)
      ret.push_back({ i + 1, smudge_count});
  }
  return ret;
}

bool check_reflection_v_gold(std::vector<std::string> block, std::pair<int, bool> id) {
  int smudges = 0;
  for (int distance = 0; id.first + distance < block.back().size() && id.first - (distance+1) >= 0; distance++) {
    for (int j = 0; j < block.size(); j++) {
      if (block[j][id.first + distance] != block[j][id.first-(distance + 1)]) {
        smudges++;
        if (smudges > 1)
          return 0;
      }
    }
  }
  return smudges != 1 ? 0 : 1;
}

std::vector<std::pair<int,bool>> find_horizontal_gold(std::vector<std::string> block) {
  std::vector<std::pair<int,bool>> ret;
  for (int i = 0; i < block.size() - 1; i++) {
    int smudge_count = 0;
    for (int j = 0; j < block.back().size(); j++) {
      if (block[i][j] != block[i+1][j])
        smudge_count++;
    }
    if (smudge_count < 2)
      ret.push_back({ i + 1, smudge_count});
  }
  return ret;
}

bool check_reflection_h_gold(std::vector<std::string> block, std::pair<int, bool> id) {
  int smudges = 0;
  for (int distance = 0; id.first + distance < block.size() && id.first - (distance+1) >= 0; distance++) {
    for (int j = 0; j < block.back().size(); j++) {
      if (block[id.first + distance][j] != block[id.first-(distance + 1)][j]) {
        smudges ++;
        if (smudges > 1)
          return 0;
      }
    }
  }
  return smudges != 1 ? 0 : 1;
}

int main() {
  std::string line;
  std::vector<std::vector<std::string>> blocks;
  std::vector<std::string> block;

  int silver = 0;
  int gold = 0;
  while (std::getline(std::cin, line)) {
    if (line.length() == 0) {
      blocks.push_back(block);
      block.clear();
      continue;
    }
    block.push_back(line);
  }
  if (block.size() != 0)
    blocks.push_back(block);

  for ( auto x : blocks) {
    std::vector<int> h_candidates = find_horizontal(x);
    std::vector<std::pair<int,bool>> h_candidates_gold = find_horizontal_gold(x);
    std::vector<int> v_candidates = find_vertical(x);
    std::vector<std::pair<int,bool>> v_candidates_gold = find_vertical_gold(x);

    for (auto h : h_candidates) {
      if (check_reflection_h(x, h)) 
        silver += h * 100;
    }
    for (auto v : v_candidates) {
      if (check_reflection_v(x, v)) 
        silver += v;
    }
    for (auto h : h_candidates_gold) {
      if (check_reflection_h_gold(x, h)) {
        gold += h.first * 100;
      }
    }
    for (auto v : v_candidates_gold) {
      if (check_reflection_v_gold(x, v))  {
        gold += v.first;
      }
    }
  }
  std::cout<<silver<<"\n";
  std::cout<<gold<<"\n";
}
