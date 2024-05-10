#include <iostream>
#include <vector>
#include <algorithm>
#include <array>

bool joker = 0; // :)
enum {UNIQUE, PAIR, TWO_PAIR, TRIPLE, FULL_HOUSE, FOUR, FIVE};

int to_numeric(char x) {
  if (isdigit(x)) 
    return x - 0x30 - 2 + joker;
  else switch(x) {
    case 'T': return 8 + joker;
    case 'J': return joker ? 0 : 9;
    case 'Q': return 10;
    case 'K': return 11;
    case 'A': return 12;
  }
  return -1;
}

int evaluate(std::string a) {
  std::array<int,13> values = {0};
  for (auto x : a)
    values[to_numeric(x)]++;

  std::sort(values.begin() + joker, values.end());
  if (joker)
    values[12] += values[0];

  if (values[12] == 5) return FIVE;
  if (values[12] == 4) return FOUR;
  if (values[12] == 3 && values[11] == 2) return FULL_HOUSE;
  if (values[12] == 3) return TRIPLE;
  if (values[12] == 2 && values[11] == 2) return TWO_PAIR;
  if (values[12] == 2) return PAIR;
  return UNIQUE;
}

int compare(std::pair<std::string, uint64_t>& a, std::pair<std::string, uint64_t>& b) {
  int l = evaluate(a.first);
  int r = evaluate(b.first);

  if (l == r)
    for (int i = 0; i < 5; i++) {
      if (to_numeric(a.first[i]) > to_numeric(b.first[i]))
        return false;
      if (to_numeric(a.first[i]) < to_numeric(b.first[i]))
        return true;
    }
  
  return l < r;
}

int main() {
  std::string in;
  uint64_t temp, silver = 0, gold = 0;
  std::vector<std::pair<std::string, uint64_t>> hands;
  while (std::cin >> in >> temp) 
    hands.push_back({in, temp});

  std::sort(hands.begin(), hands.end(), compare);
  for (int i = 0; i < hands.size(); i++)
    silver += hands[i].second * (i + 1);

  joker = 1;
  std::sort(hands.begin(), hands.end(), compare);
  for (int i = 0; i < hands.size(); i++)
    gold += hands[i].second * (i + 1);

  std::cout<<"Silver: "<<silver<<"\n";
  std::cout<<"Gold: "<<gold<<"\n";
}
