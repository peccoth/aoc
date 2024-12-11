#include <iostream>
#include <cmath>
#include <unordered_map>

unsigned long ipow(unsigned long base, int exp) {
    unsigned long result = 1;
    for (;;) {
        if (exp & 1)
            result *= base;
        exp >>= 1;
        if (!exp)
            break;
        base *= base;
    }
    return result;
}

auto blink(auto& stones) {
  std::unordered_map<unsigned long, unsigned long> new_stones{};
  for (auto [stone, counter] : stones) {
    unsigned long l = log10(stone) + 1;
    if (stone == 0){
      new_stones[1] += counter;
    } else if (l > 0 && !(l&1)) {
      unsigned long div = (stone) / ipow(10, l/2);
      unsigned long mod = (stone) % ipow(10, l/2);
      new_stones[div] += counter;
      new_stones[mod] += counter;
    } else {
      new_stones[stone*2024] += counter;
    }
  }

  return new_stones;
}

int main() {
  std::unordered_map<unsigned long, unsigned long> stones = {};

  int temp;
  while (std::cin>>temp) {
    stones[temp] ++;
  }

  for (int i = 0; i < 75; i++) {
    if (i == 25) {
      unsigned long silver = 0;
      for (auto [l, r] : stones) {
        silver += r;
      }
      std::cout<<"Silver: "<<silver<<std::endl;
    }
    stones = blink(stones);
  }
  unsigned long gold = 0;
  for (auto [l, r] : stones) {
    gold += r;
  }
  std::cout<<"Gold: "<<gold<<std::endl;
}
