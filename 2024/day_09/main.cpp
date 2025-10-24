#include <iostream>
#include <tuple>
#include <vector>
#include <list>

unsigned long silver(std::vector<int> files, std::vector<int> empty_space) {
  unsigned long result = 0;
  int c_pos = 0;

  int sum = 0;
  for (auto x : files)
    sum += x;

  for (int i = 0, r = files.size() - 1; c_pos < sum; i++) {
    for (int j = 0; j < files[i]; j++) {
      result += i * c_pos++;
      if (c_pos >= sum) break;
    }
    files[i] == 0;
    int z = empty_space[i];
    empty_space[i] = 0;
    for (int j = 0; j < z; j++) {
      if (files[r] > 0)
        files[r]--;
      else {
        r--;
        files[r]--;
      }
      if (c_pos >= sum) break;
      result += r * c_pos++;
    }
  }
  return result;
}

unsigned long gold(std::string in) {
  std::list<std::tuple<int,int,int>> new_files;
  bool flip = 1;
  int num_id = 0;
  for (int i = 0; i < in.size(); i++) {
    new_files.push_back({flip, in[i] - '0', flip ? num_id : -1});
    num_id += flip;
    flip ^= 1;
  }

  for (auto x = new_files.rbegin(); x != new_files.rend(); x++) {
    auto candidate = x;
    const auto [a, b, c] = *x;
    if (a) {
      for (auto y = x; y != new_files.rend(); y++) {
        const auto [ay, by, cy] = *y;
        if (!ay && by >= b) {
          candidate = y;
        }
      }
      if (candidate == x) continue;
      std::get<1>(*candidate) -= b;
      std::get<0>(*x) = 2;
      candidate++;
      new_files.insert(candidate.base(), {a,b,c});
    }
  }
  unsigned long result = 0;
  int pos = 0;
  for (auto [l, m, r] : new_files) {
    if (l == 1) {
     while ( m --> 0) {
        result += r * pos++;
     }
    }
    if (l = -1) {
      while ( m --> 0 )
        pos++;
    }
  }
  return result;
}

int main() {
  std::string input;
  std::cin>>input;

  bool state = 0;
  std::vector<int> files;
  std::vector<int> empty_space;

  for (auto x : input) {
    if (state) {
      empty_space.push_back(x - '0');
    } else {
      files.push_back(x - '0');
    }
    state ^= 1;
  }

  std::cout<<"Silver: "<<silver(files, empty_space)<<std::endl;
  std::cout<<"Gold: "<<gold(input)<<std::endl;
}
