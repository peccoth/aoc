#include <iostream>
#include <print>

bool isInvalid(uint64_t n, uint32_t d, bool silver = false) {
  std::string s = std::to_string(n);
  const uint32_t len = s.length();
  if (silver) {
    d = 2;
  } else {
    d = len / d;
  }
  if (len % d != 0) return 0;

  for (int i = 0; i < len / d; i++)  {
    char ref = s[i];

    for (int j = 1; j < d; j++) {
      if (ref != s[(len/d)*j+i]) {
        return 0;
      }
    }
  }
  return 1;
}


bool isInvalidGold(uint64_t n) {
  std::string s = std::to_string(n);
  const uint32_t candidates = s.length() / 2 + 1;

  for (int i = 1; i < candidates; i++) {
    if (isInvalid(n, i)) {
      return 1;
    }
  }
  return 0;
}

int main() {
  std::string line;
  uint64_t silver = 0, gold = 0;
  while (std::getline(std::cin, line, ',')) {
    uint64_t l = stoull(line.substr(0,line.find('-')));
    uint64_t r = stoull(line.substr(line.find('-') + 1));

    for (uint64_t i = l; l <= r; l++) {
      silver += isInvalid(l, 1, 1) * l;
      gold += isInvalidGold(l) * l;
    }
  }
  std::println("Silver: {}", silver);
  std::println("Gold: {}", gold);
}
