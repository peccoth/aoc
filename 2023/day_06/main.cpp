#include <iostream>
#include <sstream>
#include <vector>

int main() {
  std::string line;
  std::getline(std::cin, line);
  std::stringstream ss(line);
  std::vector<int> time;
  std::vector<int> record;
  unsigned long long left = -1, right = 0;
  int silver = 1;
  unsigned long long gold = 0;
  
  ss.ignore(line.length(), ':');
  line = "";
  int temp;

  while (ss >> temp) {
    time.push_back(temp);
    line += std::to_string(temp);
  }

  unsigned long long gold_time = stoi(line);
  std::getline(std::cin, line);
  ss.clear();
  ss.str("");
  ss << line;
  ss.ignore(line.length(), ':');
  line = "";
  while (ss >> temp){
    record.push_back(temp);
    line += std::to_string(temp);
  }

  unsigned long long gold_record = stoull(line);

  for (int i = 0; i < time.size(); i++) {
    left = -1;
    for (int j = 0; j < time[i]; j++) {
      if ( j * (time[i] - j) > record[i])  {
        left = left == -1 ? j : left; 
        right = j;
      }
    }
    silver *= (right - left + 1);
  }

  
  left = -1;
  for (int i = 0; i < gold_time; i++) {
    if (i * (gold_time - i) > gold_record) {

        left = left == -1 ? i : left; 
        right = i;
    }
  }

  gold = right - left + 1;
  std::cout<<silver<<"\n";
  std::cout<<gold<<"\n";
}
