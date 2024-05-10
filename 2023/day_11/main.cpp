#include <iostream>
#include <vector>
#include <stdlib.h>

int main() {
  std::string line;
  std::vector<std::string> observation;
  std::vector<int> empty_rows;
  std::vector<int> empty_columns;
  std::vector<std::pair<int,int>> galaxies;


  while (std::getline(std::cin, line)) 
    observation.push_back(line);

  for (int i=0; i < observation.size(); i++) {
    bool is_empty = 1;
    for (int j=0; j < observation.back().size(); j++) {
      if (observation[i][j]!= '.') {
        is_empty = 0;
        break;
      }
    }
    if (is_empty) {
      empty_rows.push_back(i);
    }
  }
  for (int i=0; i < observation.size(); i++) {
    bool is_empty = 1;
    for (int j=0; j < observation.back().size(); j++) {
      if (observation[j][i]!= '.') {
        is_empty = 0;
        break;
      }
    }
    if (is_empty) {
      empty_columns.push_back(i);
    }
  }

  for (int i=0; i < observation.size(); i++) {
    bool is_empty = 1;
    for (int j=0; j < observation.back().size(); j++) {
      if (observation[i][j]== '#')
        galaxies.push_back({i,j});
    }
  }

  std::vector<uint64_t> distances;
  std::vector<uint64_t> gold_distances;
  for (int i = 0; i < galaxies.size(); i++) {
    for (int j = i+1; j < galaxies.size(); j++) {
      int empty_row_count = 0;
      int empty_col_count = 0;
      for (int z = 0; z < empty_rows.size(); z++)
        empty_row_count += empty_rows[z] > galaxies[i].first && empty_rows[z] < galaxies[j].first ||
                           empty_rows[z] < galaxies[i].first && empty_rows[z] > galaxies[j].first ;

      for (int z = 0; z < empty_columns.size(); z++)
        empty_col_count += empty_columns[z] > galaxies[i].second && empty_columns[z] < galaxies[j].second ||
                           empty_columns[z] < galaxies[i].second && empty_columns[z] > galaxies[j].second ;

      int smaller = i > j ? j : i;
      int larger = i < j ? j : i;
      distances.push_back(abs(galaxies[i].first - galaxies[j].first) + abs(galaxies[i].second - galaxies[j].second) + empty_row_count + empty_col_count);
      gold_distances.push_back(abs(galaxies[i].first - galaxies[j].first) + abs(galaxies[i].second - galaxies[j].second) + empty_row_count * 999999 + empty_col_count * 999999);
    }
  }
  uint64_t silver = 0;
  for (auto value : distances) {
    silver += value;
  }
  uint64_t gold = 0;
  for (auto value : gold_distances) {
    gold += value;
  }
  std::cout<<silver<<"\n";
  std::cout<<gold<<"\n";

}
