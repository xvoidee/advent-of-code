#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <set>

struct Antenna {
  int  x;
  int  y;
  char f;
};

int main()
{
  std::fstream f("input.txt");
  std::string l;
  std::vector<std::string> map;

  while (f >> l) {
    map.push_back(l);
  }

  int h = map.size();
  int w = map[0].size();

  std::vector<Antenna> antennas;

  for (int y = 0; y < h; ++y) {
    for (int x = 0; x < w; ++x) {
      const char frequency = map[y][x];

      if (frequency == '.') {
        continue;
      }

      antennas.push_back({x, y, frequency});
    }
  }

  std::sort(antennas.begin(), antennas.end(),
    [] (const Antenna & a, const Antenna & b) -> bool {
      return a.f < b.f;
    }
  );

  auto try_fit = [&] (int x, int y, std::set<std::pair<int, int>> & antinodes) {
    if ((x >= 0) && (y >= 0) && (x < w) && (y < h)) {
      antinodes.insert({x, y});
    }
  };

  auto count_antinodes = [&] (int s, int e, std::set<std::pair<int, int>> & antinodes) {
    if (e == s) {
      return;
    }

    for (int i = s; i <= e - 1; ++i) {
      for (int j = i + 1; j <= e; ++j) {
        const auto a = antennas[i];
        const auto b = antennas[j];

        const int dx = b.x - a.x;
        const int dy = b.y - a.y;

        try_fit(b.x + dx, b.y + dy, antinodes);
        try_fit(a.x - dx, a.y - dy, antinodes);
      }
    }
  };

  int  start     = -1;
  int  end       = -1;
  char frequency = '?';

  std::set<std::pair<int, int>> antinodes;

  for (int i = 0; i < antennas.size(); ++i) {
    const auto a = antennas[i];
    const char f = a.f;

    if (f != frequency) {
      count_antinodes(start, end, antinodes);

      start     = i;
      end       = i;
      frequency = f;
      continue;
    }

    end = i;

    if (i == antennas.size() - 1) {
      count_antinodes(start, end, antinodes);
    }
  }

  std::cout << antinodes.size() << '\n';

  return 0;
}

