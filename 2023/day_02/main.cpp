#include<iostream>
#include<sstream>

int main() {
  int silver = 0;
  int gold = 0;
  std::string line;
  while (std::getline(std::cin,line)) {
    std::istringstream iss(line);
    std::string color;
    int min_r = 0, min_g = 0, min_b = 0;
    int game_id;
    int curr_amount;
    bool game_ok = 1;
    
    iss >> color;
    iss >> game_id;

    iss >> color;
    //
    while (iss >> curr_amount) {
      iss >> color;
      if (game_ok >= 1) 
        switch (color[0]) {
          case 'b':
            game_ok = curr_amount < 15;
            break;
          case 'g':
            game_ok = curr_amount < 14;
            break;
          case 'r':
            game_ok = curr_amount < 13;
            break;
        }
      switch (color[0]) {
        case 'b':
          min_b = min_b > curr_amount ? min_b : curr_amount;
          break;
        case 'g':
          min_g = min_g > curr_amount ? min_g : curr_amount;
          break;
        case 'r':
          min_r = min_r > curr_amount ? min_r : curr_amount;
          break;
      }
    }


    gold += (min_r * min_g * min_b);
    silver += game_id * game_ok;

  }

  std::cout<<"Silver: "<<silver<<"\n";
  std::cout<<"Gold: "<<gold<<"\n";
}
