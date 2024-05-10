#include <iostream>
#include <sstream>
#include <unordered_set>
#include <vector>

int main() {
  std::string line;
  int silver = 0;
  int gold = 0;
  std::vector<int> wins;
  std::vector<int> cards;
  while(std::getline(std::cin,line)) {
    std::stringstream a(line);
    std::string temp;
    std::unordered_set<int> winning;
    a >> temp;
    a >> temp;
    while (a >> temp) {
      if (temp == "|")
        break;
      winning.insert(stoi(temp));
    }


    uint32_t score = 0;
    while (a >> temp) {
      if (winning.contains(stoi(temp))) {
        score = score == 0 ? 1 : score << 1;
      }
    }
    
    wins.push_back(score == 0 ? 0 : __builtin_ctz(score) + 1);
    cards.push_back(1);
    silver += score;
  }
  for (int i = 0; i < wins.size(); i++) {
    for (int j = 0; j < wins[i]; j++) {
      cards[i + j + 1] += cards[i];
    }
  }
  for (auto x : cards)
    gold += x;

  std::cout<<"Silver: "<<silver<<"\n";
  std::cout<<"Gold: "<<gold<<"\n";
}
