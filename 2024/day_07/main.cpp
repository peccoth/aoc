#include <iostream>
#include <sstream>
#include <vector>

bool possible(auto l, auto& r, bool gold = 0) {
  if (r.size() == 1 && r[0] != l)
    return 0;
  if (r.size() == 1 && r[0] == l)
    return 1;

  std::vector<unsigned long> copy_plus = { r[0] * r[1] };
  copy_plus.insert(copy_plus.begin()+1, r.begin()+2, r.end());

  std::vector<unsigned long> copy_multiply = { r[0] + r[1] };
  copy_multiply.insert(copy_multiply.begin()+1, r.begin()+2, r.end());

  if (gold) {
    std::string temp = std::to_string(r[0]) + std::to_string(r[1]);
    std::vector<unsigned long> copy_concat = { std::stoul(temp) };
    copy_concat.insert(copy_concat.begin()+1, r.begin()+2, r.end());
    return possible(l, copy_plus, 1) + possible(l, copy_multiply, 1) + possible(l, copy_concat, 1);
  }

  return possible(l, copy_plus) + possible(l, copy_multiply);
}

int main() {
  std::string line, temp;
  unsigned long silver = 0;
  unsigned long gold = 0;

  while (std::getline(std::cin,line)) {
    std::stringstream ss(line);
    std::getline(ss,temp, ':');
    const unsigned long l = std::stoul(temp);

    std::vector<unsigned long> r;
    while (ss >> temp) {
      unsigned long temp_i = stoul(temp);
      r.push_back(temp_i);
    }
   if (possible(l, r))
      silver += l;

   if (possible(l, r, 1))
      gold += l;
  }
  std::cout<<"Silver: "<< silver<<std::endl;
  std::cout<<"Gold: "<< gold<<std::endl;
}
