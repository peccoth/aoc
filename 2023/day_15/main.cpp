#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
int hash(std::string in) {
  int ret = 0;
  if (in.back() == '\n') 
    in = in.substr(0,in.length()-1); // ostatni element ma \n na końcu

  for (char c : in) {
    ret += c;
    ret *= 17;
    ret %= 256;
  }

  return ret;
}

int main() {
  std::string str;
  int silver = 0;
  int gold = 0;
  std::array<std::vector<std::pair<std::string, int>>,256> boxes;

  while (std::getline(std::cin, str, ',')) {
    silver += hash(str);

    size_t eq_pos = str.find('=');
    size_t da_pos = str.find('-');
    char op = eq_pos < da_pos ? '=' : '-';
    std::string curr_label = str.substr(0, eq_pos < da_pos ? eq_pos : da_pos);
    int curr_hash = hash(curr_label);

    int focal_length = 0;
    if (eq_pos < da_pos)
      focal_length = stoi(str.substr(eq_pos+1));

    if (op == '=') {
      bool inserted = 0;
      for (int i = 0; i < boxes[curr_hash].size(); i++) {
        if (boxes[curr_hash][i].first == curr_label) {
          boxes[curr_hash][i].second = focal_length;
          inserted = 1;
        }
      }

      if (!inserted)
        boxes[curr_hash].push_back({curr_label, focal_length});
    } else {
      for (auto it = boxes[curr_hash].begin(); it != boxes[curr_hash].end(); ) {
        auto c = *it;
        if (c.first == curr_label) {
          boxes[curr_hash].erase(it);
        } else
          it++;
      }
    }
  }

  for (int i = 0; i < 256; i++) {
    for (int j = 0; j < boxes[i].size(); j++) {
      gold += (i+1) * (j+1) * boxes[i][j].second;
    }
  }

  std::cout<<silver<<"\n";
  std::cout<<gold<<"\n";
}
