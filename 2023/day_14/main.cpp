#include <iostream>
#include <vector>
#include <map>

typedef std::vector<std::string> grid;
      
void roll_the_ball(grid& result, int i, int j, int d) {
  const int dir[][2] = {{ -1,  0 }, 
                        {  0, -1 }, 
                        {  1,  0 }, 
                        {  0,  1 }};
  while (1) 
  {
    bool position_valid = 1;
    if ( d == 0 && i < 1 ||
         d == 1 && j < 1 || 
         d == 2 && i + 1 >= result.size() ||
         d == 3 && j + 1 >= result.back().size() )
      position_valid = 0;
      

    if (!position_valid || 
        result[i + dir[d][0]][j + dir[d][1]] != '.') 
    {
      result[i][j] = 'O';
      break;
    }

    i += dir[d][0]; // -1
    j += dir[d][1]; //  0
  }
}

int calculate_score(grid& result) {
  int silver = 0;
  for (int i = 0; i < result.size(); i++) {
    for (int j = 0; j < result.back().size(); j++)
      if (result[i][j] == 'O')
        silver += result.size() - i;
  }
  return silver;
}

int main() {
  grid table;
  grid clean_table;
  grid result;
  std::string line;

  while (std::getline(std::cin, line)) {
    table.push_back(line);
  }

  for (int i = 0; i < table.size(); i++) {
    std::string new_line = "";
    for (int j = 0; j < table.back().size(); j++) {
      if (table[i][j] == '#')
        new_line += '#';
      else 
        new_line += '.';
    }
    clean_table.push_back(new_line);
  }

  std::map<uint64_t, std::vector<int>> past_scores;
  std::map<grid, int> cycle_detection;
  uint64_t target = 1000000000;
  for (uint64_t gold = 0; gold < target; gold ++) {
    for (int d = 0; d < 2; d++) {
      result = clean_table;
      for (int i = 0; i < table.size(); i++) {
        for (int j = 0; j < table.back().size(); j++) {
          if (table[i][j] == 'O')
            roll_the_ball(result, i, j, d);
        }
      }
      if (d == 0 && gold == 0) 
        std::cout<<"Silver: "<<calculate_score(result)<<"\n";
      table = result;
    }
    for (int d = 2; d < 4; d++) {
      result = clean_table;
      for (int i = table.size()-1; i >= 0; i--) {
        for (int j = table.back().size(); j >= 0; j--) {
          if (table[i][j] == 'O')
            roll_the_ball(result, i, j, d);
        }
      }
      table = result;
    }
    if (cycle_detection.contains(table)) {
      int cycle_size = gold - cycle_detection[table];
      gold = target - (target - gold) % cycle_size;
    } else {
      cycle_detection[table] = gold;
    }
  }
  std::cout<<"Gold: "<<calculate_score(result)<<"\n";
}
