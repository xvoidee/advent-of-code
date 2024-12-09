#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <tuple>
#include <bitset>

#include <cstring>

using Waypoint = std::tuple<int, int, char>;
using Path     = std::vector<Waypoint>;

int main()
{
  std::fstream f("input.txt");

  const int w = 130;
  const int h = 130;

  char map[h][w + 1];

  {
    int r = 0;
    std::string l;
    while (f >> l) {
      strcpy(map[r], l.c_str());
      r++;
    }
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

  auto build_default_path = [&] () -> Path {
    int  x = start_x;
    int  y = start_y;
    char d = start_d;

    Path p;

    while (true) {
      if ((y < 0) || (y == h) || (x < 0) || (x == w)) {
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
      if ((y < 0) || (y == h) || (x < 0) || (x == w)) {
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

  std::vector<Waypoint> default_path = build_default_path();
  std::bitset<w * h> obstacles;
  int amount = 0;

  for (int i = 1; i < default_path.size(); ++i) {
    const int obstacle_y = std::get<0>(default_path[i]);
    const int obstacle_x = std::get<1>(default_path[i]);
    const int unused     = std::get<2>(default_path[i]);

    const int bit = obstacle_y * w + obstacle_x;

    if (obstacles[bit]) {
      continue;
    }

    map[obstacle_y][obstacle_x] = '#';

    std::set<Waypoint> path;
    if (is_loop(path)) {
      obstacles[bit] = true;
      amount++;
    }

    map[obstacle_y][obstacle_x] = '.';
  }

  std::cout << amount << '\n';

  return 0;
}

