#include <iostream>
#include <ranges>

int main() {
  int silver = 0, gold = 0; 

  std::string a;
  const std::string nums[] = { "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };
  while (std::cin >> a) {
    int l = -1, r = -1;
    for (auto& x : a) 
      if (isdigit(x)) {
        l = x-48;
        break;
      }
    
    for (auto& x : a | std::views::reverse) 
      if (isdigit(x)) {
        r = x-48;
        break;
      }

    silver += (l * 10 + r);

    size_t lid = a.find(l + 48);
    size_t rid = a.rfind(r + 48);

    for (int i = 0; i < 9; ++i) {
      size_t tmp = a.find(nums[i]);
      if (tmp < lid) {
        l = i + 1;
        lid = tmp;
      }
    }

    for (int i = 0; i < 9; ++i) {
      size_t tmp = a.rfind(nums[i]);
      if (tmp > rid && tmp != std::string::npos) {
        r = i + 1;
        rid = tmp;
      }
    }

    gold += (l * 10 + r);
  }

  std::cout<<"Silver: "<<silver<<"\n";
  std::cout<<"Gold: "<<gold<<"\n";
}
