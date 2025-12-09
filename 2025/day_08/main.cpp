#include <cmath>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <print>
#include <vector>
#include <ranges>
#include <string_view>
#include <unordered_set>

struct Point {
  uint64_t x, y, z;
};

auto distance (Point p1, Point p2) -> double {
  const double ret = sqrt(
        ((p1.x - p2.x) * (p1.x - p2.x))
      + ((p1.y - p2.y) * (p1.y - p2.y))
      + ((p1.z - p2.z) * (p1.z - p2.z))
    );
  return ret;
}

auto get_input() -> std::vector<Point> {
  std::vector<Point> input;
  std::string line;
  while (std::getline(std::cin, line)) {
    std::string_view sv(line);
    auto i = std::views::split(sv, ',') 
        | std::views::transform([](auto r) { return std::string_view(r);}) 
        | std::views::transform([](auto r) { int ret; std::from_chars(r.data(), r.data() + r.size(), ret); return ret; })
        | std::ranges::to<std::vector<uint64_t>>();

    Point P = {i.at(0), i.at(1), i.at(2)};
    input.emplace_back(P);
  } 

  return input;
}

auto get_distances(const auto& input) -> std::vector<std::tuple<int,int,double>> {
  std::vector<std::tuple<int,int,double>> distances;
  std::ranges::for_each(
      std::views::iota(std::size_t{0}, input.size())
      , [&](size_t x) {
      std::ranges::for_each(
          std::views::iota(std::size_t{0}, input.size())
          , [&](size_t y) {
          if (x >= y) return;
          auto t = distance(input.at(x), input.at(y));
          distances.emplace_back(x, y, t);
      });
  });
  std::ranges::sort(distances, [](auto x, auto y) {return get<2>(x) < get<2>(y);});
  return distances;
}

auto prepare_junctions(const auto& input) {
  std::vector<std::unordered_set<size_t>> junctions;
  std::ranges::for_each(std::views::iota(std::size_t{0}, input.size()), 
      [&](auto i) {junctions.emplace_back(std::unordered_set<size_t>{i});});
  return junctions;
}

auto connect_junctions(const auto& distances, auto& junctions, bool gold = 0) -> uint64_t {
  uint64_t res = 1;
  int circuits = 0;
  auto find_connection = [&](size_t i) {
    auto [x, y, _] = distances.at(i);
    int found_l = 0, found_r = 0;
    bool rl = 0, rr = 0;
    for (int i = 0; i < junctions.size(); i++) {
      bool l = rl ? 0 : junctions[i].contains(x);
      bool r = rr ? 0 : junctions[i].contains(y);
      if (l) {
        found_l = i;
        rl = 1;
      }
      if (r) {
        found_r = i;
        rr = 1;
      }
    }

    if ( rl && rr && found_l != found_r) {
      junctions[found_l].insert(junctions[found_r].begin(), junctions[found_r].end());
      junctions.erase(junctions.begin() + found_r);
    }     

    if (gold) {
      circuits = junctions.size();
      if (circuits == 1)
        return i;
    }
    
    return size_t{0};
  };

  if (!gold) {
    std::ranges::for_each(std::views::iota(std::size_t{0}, std::size_t{1000}), find_connection);
    std::ranges::sort(junctions, [](auto x, auto y) {return x.size() > y.size();});
    res *= junctions[0].size() * junctions[1].size() * junctions[2].size();
  } else {
    auto gold_i = std::ranges::find_if(std::views::iota(std::size_t{0}, distances.size()), find_connection);
    res = *gold_i;
  }

  return res;
}

auto main() -> int {
  auto input = get_input();
  auto distances = get_distances(input);
  auto junctions = prepare_junctions(input);
  std::println("Silver: {}",connect_junctions(distances,junctions));

  auto [x, y, _] = distances[connect_junctions(distances,junctions,1)];
  auto g1 = input[x].x;
  auto g2 = input[y].x;
  std::println("Gold: {}", g1 * g2);
}
