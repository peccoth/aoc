#include <iostream>
#include <sstream>
#include <vector>
#include <tuple>
#include <map>


std::map<std::tuple<int, int, int>, uint64_t> sad;
uint64_t recurse(const std::string& str, const std::vector<uint64_t>& target, int str_pos, int target_pos, int curr) {
  std::tuple<int, int, int> key = std::make_tuple(str_pos, target_pos, curr);
  if (sad.contains(key))
    return sad[key];
  if (str_pos == str.length()) {
    if (target_pos == target.size() && curr == 0)
      return 1;
    if (target_pos == target.size() - 1 && curr == target.back())
      return 1;
    else 
      return 0;
  }
  uint64_t counter = 0; 
  for (auto c : { '.', '#' }) {
    if (str[str_pos] == c || str[str_pos] == '?')
      if (c == '.' && curr == 0) {
        counter += recurse(str, target, str_pos+1, target_pos, curr);
      } else if (c == '.' && curr > 0 && curr == target[target_pos]) {
        counter += recurse(str, target, str_pos+1, target_pos+1, 0);
      } else if (c == '#')
        counter += recurse(str, target, str_pos+1, target_pos, curr+1);
  }
  sad[key] = counter;
  return counter;
}

std::string to_big_string(const std::string str) {
  return str + '?' + str + '?' + str + '?' + str + '?' + str;
}
std::vector<uint64_t> to_big_numbers(const std::vector<uint64_t> numbers) {
  std::vector<uint64_t> big_nums;
  for (uint64_t i = 0; i < 5; i++){
    for ( auto x : numbers)
      big_nums.push_back(x);
  }
  return big_nums;
}

int main() {
  std::string a;
  uint64_t silver = 0;
  uint64_t gold = 0;
  int counter = 0;
  time_t start = time(NULL);

  while (std::getline(std::cin, a)) {
    std::string l, r;
    std::stringstream ss(a);
    std::vector<uint64_t> numbers;
    ss >> l;
    while (std::getline(ss, r, ',')) 
      numbers.push_back(stoul(r));

    silver += recurse(l, numbers, 0, 0, 0);
    sad.clear();
    gold += recurse(to_big_string(l), to_big_numbers(numbers), 0, 0, 0);
    sad.clear();
  }

  std::cout<<"Silver: "<<silver<<"\n";
  std::cout<<"Gold: "<<gold<<"\n";
}
