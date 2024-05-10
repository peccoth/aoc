#include <iostream>
#include <map>
#include <algorithm>
#include <sstream>
#include <vector>

uint64_t gcd(uint64_t a, uint64_t b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

uint64_t lcm(std::vector<int> in) {
    uint64_t ret = in[0];
 
    for (int i = 1; i < in.size(); i++)
        ret = in[i] * ret / gcd(in[i], ret);
 
    return ret;
}

int main() {
  std::string instructions;
  std::cin>>instructions;

  std::map<std::string,std::pair<std::string,std::string>> moves;
  std::vector<std::string> ghosts;
  std::string line;
  std::string a, b, c;
  int A_counter = 0;
  while (std::getline(std::cin, line)) {
    if (line[0] == '\0')
      continue;
    line.erase(std::remove_if(line.begin(), line.end(), 
               [](unsigned char x) {
               char to_remove[] = {'=', '(', ')', ','};
               for (int i = 0; i < 4; i++)
                if (x == to_remove[i])
                  return 1;
               return 0;
               }), line.end());

    std::stringstream ss(line);
    ss >> a >> b >> c;

    if (a[a.length()-1] =='A')
      ghosts.push_back(a);
    
    moves[a] = {b, c};
  }

  int silver = 0;
  std::string curr = "AAA";
  while (curr != "ZZZ") {
    char next = instructions[silver%instructions.size()];
    if (next == 'L')
      curr = moves[curr].first;
    if (next == 'R')
      curr = moves[curr].second;
    silver++;
  }
  std::cout<<"Silver: "<<silver<<"\n";

  std::vector<int> ghost_steps;
  for (int i = 0; i < ghosts.size(); i++) {
    curr = ghosts[i];
    uint64_t step = 0;
    while (curr[2] != 'Z') {
      char next = instructions[step%instructions.size()];
      if (next == 'L')
        curr = moves[curr].first;
      if (next == 'R')
        curr = moves[curr].second;
      step++;
    }
    ghost_steps.push_back(step);
  }
  std::cout<<"Gold: "<<lcm(ghost_steps)<<"\n";
}
