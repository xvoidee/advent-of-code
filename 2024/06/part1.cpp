#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <set>

int main()
{
  std::fstream f("input.txt");
  std::string l;
  std::vector<std::string> map;

  while (f >> l) {
    map.push_back(l);
  }

  int  y = 0;
  int  x = 0;
  char d = '^';

  for (auto & r : map) {
    x = 0;
    bool found = false;
    for (auto & c : r) {
      if (c == '^') {
        found = true;
        c = '.';
        break;
      }
      x++;
    }

    if (found) {
      break;
    }

    y++;
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

  std::set<std::pair<int, int>> path;

  while (true) {
    if ((y < 0) || (y == map.size()) || (x < 0) || (x == map[0].size())) {
      break;
    }

    if (map[y][x] == '.') {
      path.insert({y, x});
      move_forward(y, x, d);
      continue;
    }

    if (map[y][x] == '#') {
      move_backward(y, x, d);
      turn_right(d);
    }
  }

  std::cout << path.size() << '\n';

  return 0;
}

