#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <tuple>

using Waypoint = std::tuple<int, int, char>;
using Path     = std::vector<Waypoint>;

int main()
{
  std::fstream f("input.txt");
  std::string l;
  std::vector<std::string> map;

  while (f >> l) {
    map.push_back(l);
  }

  int  start_y = 0;
  int  start_x = 0;
  char start_d = '^';

  for (auto & r : map) {
    start_x = 0;
    bool found = false;
    for (auto & c : r) {
      if (c == '^') {
        found = true;
        c = '.';
        break;
      }
      start_x++;
    }

    if (found) {
      break;
    }

    start_y++;
  }

  auto move_forward = [] (int & y, int & x, char d) {
    switch (d) {
    case '^': y--; break;
    case 'V': y++; break;
    case '<': x--; break;
    case '>': x++; break;
    }
  };

  auto move_backward = [] (int & y, int & x, char d) {
    switch (d) {
    case '^': y++; break;
    case 'V': y--; break;
    case '<': x++; break;
    case '>': x--; break;
    }
  };

  auto turn_right = [] (char & d) {
    switch (d) {
    case '^': d = '>'; break;
    case '>': d = 'V'; break;
    case 'V': d = '<'; break;
    case '<': d = '^'; break;
    }
  };

  auto build_default_path = [&] (const std::vector<std::string> & map) -> Path {
    int  x = start_x;
    int  y = start_y;
    char d = start_d;

    Path p;

    while (true) {
      if ((y < 0) || (y == map.size()) || (x < 0) || (x == map[0].size())) {
        break;
      }

      if (map[y][x] == '.') {
        p.push_back({y, x, d});
        move_forward(y, x, d);
        continue;
      }

      if (map[y][x] == '#') {
        move_backward(y, x, d);
        turn_right(d);
        move_forward(y, x, d);
        continue;
      }
    }

    return p;
  };

  auto is_loop = [&] (std::set<Waypoint> & p) -> bool {
    int  y = start_y;
    int  x = start_x;
    char d = start_d;

    while (true) {
      if ((y < 0) || (y == map.size()) || (x < 0) || (x == map[0].size())) {
        return false;
      }

      Waypoint wp = {y, x, d};

      if (map[y][x] == '.') {
        if (p.find(wp) != p.end()) {
          return true;
        }

        p.insert(wp);
        move_forward(y, x, d);
        continue;
      }

      if (map[y][x] == '#') {
        move_backward(y, x, d);
        turn_right(d);
        move_forward(y, x, d);
        continue;
      }
    }

    return false;
  };

  std::vector<Waypoint> default_path = build_default_path(map);
  for (auto p : default_path) {
    auto [y, x, d] = p;
//    std::cout << y << ' ' << x << ' ' << d << '\n';
  }

  std::set<std::tuple<int, int>> obstacles;

  for (int i = 1; i < default_path.size(); ++i) {
    const int obstacle_y = std::get<0>(default_path[i]);
    const int obstacle_x = std::get<1>(default_path[i]);
    const int unused     = std::get<2>(default_path[i]);

    map[obstacle_y][obstacle_x] = '#';

    std::set<Waypoint> path;
//    for (int j = 0; j < i - 1; ++j) {
//      path.insert(default_path[j]);
//    }

//    const auto p = default_path[i - 1];
//    start_y = std::get<0>(p);
//    start_x = std::get<1>(p);
//    start_d = std::get<2>(p);

    if (is_loop(path)) {
      obstacles.insert({obstacle_y, obstacle_x});
    }

    map[obstacle_y][obstacle_x] = '.';
  }

  std::cout << obstacles.size() << '\n';

  return 0;
}

// 287.01s user 0.08s system 99% cpu 4:47.85 total
//
