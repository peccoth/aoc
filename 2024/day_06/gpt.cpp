#include <iostream>
#include <vector>
#include <set>
#include <tuple>

const std::pair<int, int> directions[] = {
    {-1, 0}, {0, 1}, {1, 0}, {0, -1} // Up, Right, Down, Left
};

typedef std::tuple<int, int, int> Position;

bool causes_loop(const std::vector<std::string>& map, Position start_pos, std::pair<int, int> obstruction) {
    std::set<Position> visited;
    auto [y, x, dir] = start_pos;
    visited.insert(start_pos);

    std::vector<std::string> new_map = map;
    new_map[obstruction.first][obstruction.second] = '#';

    while (true) {
    std::cout<<y<<" "<<x<<std::endl;
        int ny = y + directions[dir].first;
        int nx = x + directions[dir].second;
        if (ny < 0 || ny >= map.size() || nx < 0 || nx >= map[0].size()) return false;

        if (new_map[ny][nx] == '#') {
            dir = (dir + 1) % 4;
        } else {
            y = ny;
            x = nx;
        }

        Position current = {y, x, dir};

        if (visited.count(current)) return true;

        visited.insert(current);
    }
}

int main() {
    std::vector<std::string> map;
    std::string line;
    while (std::getline(std::cin, line)) {
        map.push_back(line);
    }

    Position start_pos;
    for (int y = 0; y < map.size(); y++) {
        for (int x = 0; x < map[0].size(); x++) {
            if (map[y][x] == '^') start_pos = {y, x, 0};
        }
    }

    std::set<std::pair<int, int>> candidates;
    auto [y, x, dir] = start_pos;
    while (true) {
        int ny = y + directions[dir].first;
        int nx = x + directions[dir].second;

        if (ny < 0 || ny >= map.size() || nx < 0 || nx >= map[0].size()) break;

        if (map[ny][nx] == '.') candidates.insert({ny, nx});

        if (map[ny][nx] == '#') {
            dir = (dir + 1) % 4;
        } else {
            y = ny;
            x = nx;
        }
    }

    int loop_count = 0;
    for (auto [cy, cx] : candidates) {
        if (causes_loop(map, start_pos, {cy, cx})) loop_count++;
    }

    std::cout << "Gold: " << loop_count << std::endl;
}
