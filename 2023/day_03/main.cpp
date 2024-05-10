#include<iostream>
#include<vector>

bool is_symbol(char& c) {
  if (c == 46)
    return 0;
  if (isdigit(c))
    return 0;
  return 1;
}

bool check_silver(std::vector<std::string>& input, int y, int x) {
  int ret = 0;
  if (y > 0){
    if (x > 0) 
      ret += is_symbol(input[y-1][x-1]);
    ret += is_symbol(input[y - 1][x]);
    if (x < input[x].length()-1)
      ret += is_symbol(input[y-1][x+1]);
  }
  if (y < input.size()-1){
    if (x > 0) 
      ret += is_symbol(input[y+1][x-1]);
    ret += is_symbol(input[y+1][x]);
    if (x < input[x].length()-1)
      ret += is_symbol(input[y+1][x+1]);
  }
  if (x > 0)
    ret += is_symbol(input[y][x-1]);
  if (x < input[y].length()-1) 
    ret += is_symbol(input[y][x+1]);

  return ret;
}

int full_num(std::vector<std::string>& input, int y, int x) {
  std::string curr_num = "";
  curr_num += input[y][x];
  for (int i = x; i > 0; --i) {
    if (!isdigit(input[y][i-1]))
      break;
    curr_num = input[y][i-1] + curr_num;
  }
  for (int i = x; i < input[y].length(); ++i) {
    if (!isdigit(input[y][i+1]))
      break;
    curr_num += input[y][i+1];
  }
  return stoi(curr_num);
}

int check_gold(std::vector<std::string>& input, int y, int x) {
  int out[6];
  int item_count = 0;
  if (y > 0) {
    if (isdigit(input[y-1][x])) {
      out[item_count] = full_num(input, y-1, x);
      item_count++;
    } else {
        if (x > 0 && isdigit(input[y-1][x-1])) {
          out [item_count]= full_num(input, y-1, x-1);
          item_count++;
        }
        if (x < input[y].length() - 1  && isdigit(input[y-1][x+1])) {
          out [item_count]= full_num(input, y-1, x+1);
          item_count++;
        }
    }
  }

  if (y < input.size() - 1) {
    if (isdigit(input[y+1][x])) {
      out[item_count] = full_num(input, y+1, x);
      item_count++;
    } else {
        if (x > 0 && isdigit(input[y+1][x-1])) {
          out[item_count] = full_num(input, y+1, x-1);
          item_count++;
        }
        if (x < input[y].length() - 1  && isdigit(input[y+1][x+1])) {
          out[item_count] = full_num(input, y+1, x+1);
          item_count++;
        }
    }
  }
  if (x > 0) {
    if (isdigit(input[y][x-1])) {
      out[item_count] = full_num(input, y, x-1);
      item_count++;
    }
  }

  if (x < input[y].length() - 1) {
    if (isdigit(input[y][x+1])) {
      out[item_count] = full_num(input, y, x+1);
      item_count++;
    }
  }
  if (item_count != 2)
    return 0;
  return out[0] * out[1];
}

int main() {
  std::vector<std::string> input;
  std::string line;
  int silver = 0; 
  long gold = 0;
  while (std::getline(std::cin, line))
    input.push_back(line);

  for (int i=0;i<input.size();i++) {
    std::string current_number = "";
    bool is_part = 0, is_number = 0;
    for (int j=0;j<input[i].length();j++){
      if (isdigit(input[i][j])) {
        current_number += input[i][j];
        is_part += check_silver(input,i,j);
        is_number =1;
      } else if (is_part && is_number) {
        silver += stoi(current_number);
        current_number = "";
        is_part = 0;
        is_number = 0;
      } else {
        current_number = "";
        is_part = 0;
        is_number = 0;
      }

      if (input[i][j] == '*') {
        gold += check_gold(input,i,j);
      }
    }

    if (is_part && is_number) {
      silver += stoi(current_number);
    }
  }
  std::cout<<"Silver: "<<silver<<"\n";
  std::cout<<"Gold: "<<gold<<"\n";
}
