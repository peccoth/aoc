#include <iostream>
#include <algorithm>
#include <print>
#include <vector>
#include <ranges>
#include <map>

struct Point {
  int x, y;
};

auto get_input() {
  std::vector<Point> input;
  std::string line;
  while (std::getline(std::cin, line)) {
    std::string_view sv(line);
    auto i = std::views::split(sv, ',') 
        | std::views::transform([](auto r) { return std::string_view(r);}) 
        | std::views::transform([](auto r) { int ret; std::from_chars(r.data(), r.data() + r.size(), ret); return ret; })
        | std::ranges::to<std::vector<int>>();

    Point P = {i.at(0), i.at(1)};
    input.emplace_back(P);
  } 
  return input;
}

auto silver(const auto& input) -> uint64_t {
  auto areas = std::views::all(input) | std::views::transform([&](const auto p) {
      return 
        std::views::all(input)
        | std::views::transform([p](const auto q) { 
          return static_cast<uint64_t>(abs(p.x-q.x) +1) * (abs(p.y-q.y)+1);});
      }) | std::views::join;
  return std::ranges::max(areas);
}

auto find_lines(const auto& input) {
  std::map<int, std::vector<std::pair<int, int>>> h_lines;
  std::map<int, std::vector<std::pair<int, int>>> v_lines;
  std::ranges::for_each( input | std::views::pairwise, [&](auto p) {
      auto& [prev, curr] = p;
      if (prev.x == curr.x) {
        v_lines[prev.x].emplace_back( std::make_pair(prev.y, curr.y));
      }
      if (prev.y == curr.y) {
        h_lines[prev.y].emplace_back(std::make_pair(prev.x, curr.x));
      }
      });

  return std::make_pair(h_lines, v_lines);
}

bool in_bounds(const auto& lines, const auto p, const auto q) {
  if (p.x == q.x && p.y == q.y) return 0;
  const auto& [hlines, vlines] = lines;

  const uint64_t rx = p.x > q.x ? p.x : q.x;
  const uint64_t ry = p.y < q.y ? p.y : q.y;
  const uint64_t lx = p.x < q.x ? p.x : q.x;
  const uint64_t ly = p.y > q.y ? p.y : q.y;

  bool valid = 1;

  if (valid == 0) return 0;

  for (auto it = ++hlines.find(ry); it != hlines.end(); ++it) {
    auto& [k, v] = *it;
    if (k >= ly) break;
    for (auto [l, r] : v) {
      if ((l < rx || r < rx) && (l > lx || r > lx)) valid = 0;
    }
  }

  for (auto it = ++vlines.find(lx); it != vlines.end(); ++it) {
    auto& [k, v] = *it;
    if (k >= rx) break;
    for (auto [l, r] : v) {
      if ((l < ly || r < ly) && (l > ry || r > ry)) valid = 0;
    }
  }

  return valid;
}


auto gold(const auto& input) -> uint64_t {
  auto lines = find_lines(input);
  uint64_t max = 0;
  std::ranges::for_each(input, [&](const auto p) {
       std::ranges::for_each(input, [&, p](const auto q) { 
          const uint64_t area = (abs(p.x-q.x) +1) * (abs(p.y-q.y)+1);
          if (area > max && in_bounds(lines, p, q))
            max = area;
      }); 
  });
  return max;
}

int main() {
  auto input = get_input();
  std::println("Silver: {}", silver(input));

  std::println("Gold: {}", gold(input));

}
