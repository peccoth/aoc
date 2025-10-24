#include <iostream>
#include <vector>

int rad_check(auto& input, int i, int j) {
  int ret = 0;
  if (i > 2 && j > 2)
  if (input[i-1][j-1] == 'M') { //top left
    if (input[i-2][j-2] == 'A') {
      if (input[i-3][j-3] == 'S') {
        ret++;
      }
    }
  }

  if (i > 2 && j < input[0].size() - 3)
  if (input[i-1][j+1] == 'M') { //top right
    if (input[i-2][j+2] == 'A') {
      if (input[i-3][j+3] == 'S'){
        ret++;
        }
      }
  }

  if (i > 2)
  if (input[i-1][j] == 'M') { //top
    if (input[i-2][j] == 'A') {
      if (input[i-3][j] == 'S'){
        ret++;
      }
    }
  }

  if (i < input.size() - 3)
  if (input[i+1][j] == 'M') { //bottom
    if (input[i+2][j] == 'A') {
      if (input[i+3][j] == 'S'){
        ret++;
      }
    }
  }

  if (i < input.size() - 3 && j > 2)
  if (input[i+1][j-1] == 'M') { //bottom left
    if (input[i+2][j-2] == 'A') {
      if (input[i+3][j-3] == 'S') {
        ret++;
      }
    }
  }

  if (i < input.size() - 3 && j < input[0].size() - 3)
  if (input[i+1][j+1] == 'M') { //bottom right
    if (input[i+2][j+2] == 'A') {
      if (input[i+3][j+3] == 'S') {
        ret++;
      }
    }
  }

  if (j < input[0].size() - 3)
  if (input[i][j+1] == 'M') { //right
    if (input[i][j+2] == 'A') {
      if (input[i][j+3] == 'S') {
        ret++;
      }
    }
  }

  if (j > 3)
  if (input[i][j-1] == 'M') { //right
    if (input[i][j-2] == 'A') {
      if (input[i][j-3] == 'S') {
        ret++;
      }
    }
  }

  return ret;
}
bool g_check(auto& input, int i, int j) {
  if (i < 1 || i > input.size() - 2 || j < 1 || j > input[0].size() - 2)
    return 0;
  if (input[i-1][j-1] == 'M' && 
      input[i-1][j+1] == 'M' && 
      input[i+1][j-1] == 'S' && 
      input[i+1][j+1] == 'S' ) 
    return 1;
  if (input[i-1][j-1] == 'M' && 
      input[i-1][j+1] == 'S' && 
      input[i+1][j-1] == 'M' && 
      input[i+1][j+1] == 'S' ) 
    return 1;
  if (input[i-1][j-1] == 'S' && 
      input[i-1][j+1] == 'S' && 
      input[i+1][j-1] == 'M' && 
      input[i+1][j+1] == 'M' ) 
    return 1;
  if (input[i-1][j-1] == 'S' && 
      input[i-1][j+1] == 'M' && 
      input[i+1][j-1] == 'S' && 
      input[i+1][j+1] == 'M' ) 
    return 1;
  return 0;
}

int main() {
  std::vector<std::string> input;
  std::string line;
  int silver = 0;
  int gold = 0;
  while (std::getline(std::cin, line))
    input.push_back(line);


  for (int i = 0; i < input.size(); i++) {
    for (int j = 0; j < input[0].size(); j++) {
      if (input[i][j] == 'X')
      silver += rad_check(input, i, j);
      if (input[i][j] == 'A')
      gold += g_check(input, i, j);
    }
  }
  std::cout<< silver <<std::endl;
  std::cout<< gold <<std::endl;
}
