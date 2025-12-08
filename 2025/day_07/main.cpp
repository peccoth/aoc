#include <iostream>
#include <print>
#include <vector>
#include <unordered_set>

template<class A,class B>
struct std::hash<std::pair<A,B>>{
	size_t operator() (const pair<A,B>& p) const {
		return std::rotl(hash<A>{}(p.first),1) ^
			   hash<B>{}(p.second);
	}
};

auto silver(auto manifold, auto& paths) {
  std::unordered_set<std::pair<int, int>> res;

  for (int i = 0; i < manifold[0].size(); i++) {
    if (manifold.at(0).at(i) == 'S')
      paths.at(0).at(i) = 1;
  }

  for (int i = 1; i < manifold.size(); i++) {
    for (int j = 0; j < manifold.at(0).size(); j++) {
      if (manifold.at(i).at(j) == '^' && paths.at(i-1).at(j)) {
        res.insert(std::make_pair(i,j));

        if (j > 0)
          paths.at(i).at(j-1) += paths.at(i-1).at(j);

        if (j < paths.at(0).size())
          paths.at(i).at(j+1) += paths.at(i-1).at(j);

      } else if (paths.at(i-1).at(j)) {
        paths.at(i).at(j) += paths.at(i-1).at(j);
      }
    }
  }

  return res;
}

int main() {
  std::string line;
  std::vector<std::string> manifold;
  std::vector<std::vector<uint64_t>> paths;
  while (std::getline(std::cin, line)) {
    manifold.emplace_back(line);
    paths.emplace_back(std::vector<uint64_t>(line.size(), 0));
  }
  
  auto silver_res = silver(manifold, paths);
  std::println("Silver: {}", silver_res.size());

  uint64_t gold = 0;
  for (auto x : *(paths.end()-1)) {
    gold += x;
  }
  std::println("Gold: {}", gold);
}
