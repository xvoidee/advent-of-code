#include <fstream>
#include <vector>
#include <string>
#include <iostream>

bool is_ms(const std::vector<std::string> & data, int x, int y, int dx, int dy)
{
  const char a = data[y - dy][x - dx];
  const char b = data[y + dy][x + dx];

  if ((a == 'M') && (b == 'S')) {
    return true;
  }

  if ((a == 'S') && (b == 'M')) {
    return true;
  }

  return false;
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

  int amount = 0;

  for (int y = 1; y < rows - 1; ++y) {
    for (int x = 1; x < cols - 1; ++x) {
      if (data[y][x] != 'A') {
        continue;
      }

      if (is_ms(data, x, y, 1, 1) && is_ms(data, x, y, -1, 1)) {
        amount++;
      }
    }
  }

  std::cout << amount << '\n';

  return 0;
}
