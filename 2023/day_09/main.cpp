#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <numeric>

long recurse(std::vector<long> readings) {
  bool not_zeros = 0;
  for (auto x : readings)
    if (x != 0) {
      not_zeros = 1;
      break;
    }
  if (!not_zeros)
    return 0;

  std::vector<long> new_readings;
  for (int i = 1; i < readings.size(); i++)
    new_readings.push_back(readings[i] - readings[i-1]);

  return readings.back() + recurse(new_readings);
}

int main() {
  std::string line;
  long silver = 0, gold = 0;
  while (std::getline(std::cin, line)) {
    std::vector<long> readings;
    long reading;
    std::stringstream ss(line);
    while (ss >> reading)
      readings.push_back(reading);

    silver += recurse(readings);

    std::reverse(readings.begin(), readings.end());
    if (std::accumulate(readings.begin(), readings.end(), 0) == 0)
      std::cout<<line<<"\n";

    gold += recurse(readings);
  }

  std::cout<<"Silver: "<<silver<<"\n";
  std::cout<<"Gold: "<<gold<<"\n";
}
