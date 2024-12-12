#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>

int cw;
std::vector<std::string> gold_area;
std::pair<int,int> gold_directions[140][140] = {std::make_pair(0,0)};
int next_pos(auto& area, std::pair<int,int> c_pos, std::pair<int,int> p_pos) {
  gold_area[c_pos.first][c_pos.second] = area[c_pos.first][c_pos.second];

  if (area[c_pos.first][c_pos.second] == 'S')
    return 0;
  else {
    switch (area[c_pos.first][c_pos.second]) {
      case '-':
        if (p_pos.second < c_pos.second) {
          gold_directions[c_pos.first][c_pos.second] = {1, -1};
          return 1 + next_pos(area, {c_pos.first, c_pos.second + 1}, c_pos);
        } else {
          gold_directions[c_pos.first][c_pos.second] = {-1, 1};
          return 1 + next_pos(area, {c_pos.first, c_pos.second - 1}, c_pos);
        }
      case '|':
        if (p_pos.first < c_pos.first){
          gold_directions[c_pos.first][c_pos.second] = {1, -1};
          return 1 + next_pos(area, {c_pos.first + 1, c_pos.second}, c_pos);
        }else{
          gold_directions[c_pos.first][c_pos.second] = {-1, 1};
          return 1 + next_pos(area, {c_pos.first - 1, c_pos.second}, c_pos);
        }
      case 'J':
        if (p_pos.first < c_pos.first){
          gold_directions[c_pos.first][c_pos.second] = {-1, 1};
          return 1 + next_pos(area, {c_pos.first, c_pos.second - 1}, c_pos);
        }else{
          gold_directions[c_pos.first][c_pos.second] = {1, -1};
          return 1 + next_pos(area, {c_pos.first - 1, c_pos.second}, c_pos);
        }
      case 'F':
        if (p_pos.first > c_pos.first){
          gold_directions[c_pos.first][c_pos.second] = {1, 1};
          return 1 + next_pos(area, {c_pos.first, c_pos.second + 1}, c_pos);
        }else{
          gold_directions[c_pos.first][c_pos.second] = {-1, -1};
          return 1 + next_pos(area, {c_pos.first + 1, c_pos.second}, c_pos);
        }
      case 'L':
        if (p_pos.first < c_pos.first){
          gold_directions[c_pos.first][c_pos.second] = {1, -1};
          return 1 + next_pos(area, {c_pos.first, c_pos.second + 1}, c_pos);
        }else{
          gold_directions[c_pos.first][c_pos.second] = {-1, 1};
          return 1 + next_pos(area, {c_pos.first - 1, c_pos.second}, c_pos);
        }
      case '7':
        if (p_pos.first > c_pos.first){
          gold_directions[c_pos.first][c_pos.second] = {1, -1};
          return 1 + next_pos(area, {c_pos.first, c_pos.second - 1}, c_pos);
        }else {
          gold_directions[c_pos.first][c_pos.second] = {-1, 1};
          return 1 + next_pos(area, {c_pos.first + 1, c_pos.second}, c_pos);
        }
    }
  }
  return -1;
}

bool check_dot(std::pair<int,int> c_pos) {
  while (gold_area[c_pos.first][c_pos.second] == '.'){
    c_pos.first --;
  if (c_pos.first < 0)
    return 0;
  }
  //std::cout<<gold_directions[c_pos.first][c_pos.second].first<<"\n";
  if (gold_directions[c_pos.first][c_pos.second].first == cw)
    return 1;
  return 0;
}

int main() {
  std::string line;
  std::vector<std::string> area;

  while (std::getline(std::cin, line))
    area.push_back(line);

  std::pair<int, int> S_location;
  for (int i=0; i<area.size(); i++)
    for (int j=0; j<area.back().size(); j++)
      if (area[i][j] == 'S')
        S_location = {i, j};

  for (int i = 0; i < area.size(); i++) {
    std::string nl = "";
    for (int j = 0; j< area.back().size(); j++)
      nl+='.';
    gold_area.push_back(nl);
  }

  int silver = 0;
  if (  silver ==0 &&  S_location.first > 0 && (
        area[S_location.first - 1][S_location.second] == '|' ||
        area[S_location.first - 1][S_location.second] == 'F' ||
        area[S_location.first - 1][S_location.second] == '7')){
    cw = 1;
    silver = next_pos(area, {S_location.first - 1, S_location.second}, S_location);
  }
  if (  silver ==0 && S_location.first < area.size() && (
        area[S_location.first + 1][S_location.second] == '|' ||
        area[S_location.first + 1][S_location.second] == 'J' ||
        area[S_location.first + 1][S_location.second] == 'L')){
    cw = -1;
    silver = next_pos(area, {S_location.first + 1, S_location.second}, S_location);
  }
  if (  silver ==0 && S_location.second < area.back().size() && (
        area[S_location.first][S_location.second + 1] == '-' ||
        area[S_location.first][S_location.second + 1] == 'J' ||
        area[S_location.first][S_location.second + 1] == '7')) {
    cw = 1;
    silver = next_pos(area, {S_location.first, S_location.second + 1}, S_location);
  }
  if (  silver ==0 && S_location.second > 0 && (
        area[S_location.first][S_location.second - 1] == '-' || 
        area[S_location.first][S_location.second - 1] == 'F' ||
        area[S_location.first][S_location.second - 1] == 'L')) {
    cw = 1;
    silver = next_pos(area, {S_location.first, S_location.second -1}, S_location);
  }

  int gold = 0;
//  for (auto x : gold_area)
//    std::cout<<x<<"\n";

//  for (int i = 0; i < gold_area.size(); i++){
//    for (int j = 0; j < gold_area.back().size(); j++){
//      if (gold_directions[i][j].first != -1)
//        std::cout<<" "<<gold_directions[i][j].first<<" ";
//      else
//      std::cout<<gold_directions[i][j].first<<" ";
//    }
//    std::cout<<"\n";
//  }

  for (int i=1; i < gold_area.size()-1; i++)
    for (int j=1; j < gold_area.back().size(); j++)
      if (gold_area[i][j] == '.') {
        bool c = check_dot({i,j});
        gold += c;
//        if (c)
//          std::cout<<i<<" "<<j<<"\n";
      }

  std::cout<<cw<<"\n";
  std::cout<<"Gold: "<<gold<<"\n";
  std::cout<<"Silver: "<<ceil((double)silver/2)<<"\n";
}
