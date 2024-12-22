#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <functional>

struct Point {
  int x;
  int y;

  bool operator < (const Point & b) const {
    return ((y << 16) | x) < ((b.y << 16) | b.x);
  }
};

int main()
{
  std::fstream f("input.txt");
  std::string l;
  std::vector<std::string> map;

  while (f >> l) {
    map.push_back(l);
  }

  const int h = map.size();
  const int w = map[0].size();

  std::function<void(int, int, char, std::multiset<Point> &)> hike;
  hike = [&] (int x, int y, char last, std::multiset<Point> & tops) {
    if ((x < 0) || (x == w) || (y < 0) || (y == h)) {
      return;
    }

    const int elevation = map[y][x];

    if ((elevation <= last) || ((elevation - last) > 1)) {
      return;
    }

    if (elevation == '9') {
      tops.insert({x, y});
      return;
    }

    hike(x - 1, y, elevation, tops);
    hike(x + 1, y, elevation, tops);
    hike(x, y - 1, elevation, tops);
    hike(x, y + 1, elevation, tops);
  };

  int total = 0;

  for (int y = 0; y < h; ++y) {
    for (int x = 0; x < w; ++x) {
      if (map[y][x] == '0') {
        std::multiset<Point> tops;
        hike(x - 1, y, '0', tops);
        hike(x + 1, y, '0', tops);
        hike(x, y - 1, '0', tops);
        hike(x, y + 1, '0', tops);
        total += tops.size();
      }
    }
  }

  std::cout << total << std::endl;

  return 0;
}

