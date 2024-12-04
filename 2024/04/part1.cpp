#include <fstream>
#include <vector>
#include <string>
#include <iostream>

std::string substring(const std::vector<std::string> & data, int x, int y, int dx, int dy)
{
  const int rows = data.size();
  const int cols = data[0].size();

  std::string s;

  while ((x >= 0) && (x < cols) && (y >= 0) && (y < rows) && (s.size() < 4)) {
    s += data[y][x];

    x += dx;
    y += dy;
  }

  return s;
}

int main()
{
  std::fstream f("input.txt");
  std::string s;
  std::vector<std::string> data;

  while (f >> s) {
    data.emplace_back(s);
  }

  const int rows = data.size();
  const int cols = data[0].size();

  const std::vector<std::pair<int, int>> order = {
    {  1,  0 },
    { -1,  0 },
    {  0,  1 },
    {  0, -1 },
    {  1,  1 },
    { -1, -1 },
    {  1, -1 },
    { -1,  1 }
  };

  int amount= 0;

  for (int y = 0; y < rows; ++y) {
    for (int x = 0; x < cols; ++x) {
      for (const auto & o : order) {
        if (substring(data, x, y, o.first, o.second) == "XMAS") {
          amount++;
        }
      }
    }
  }

  std::cout << amount << '\n';

  return 0;
}

