#include <fstream>
#include <iostream>
#include <vector>
#include <map>

int main()
{
  std::ifstream f("input.txt");

  int x, y;

  std::vector<int> a, b;

  while (f >> x >> y) {
    a.push_back(x);
    b.push_back(y);
  }

  auto count = [&b] (int v) -> int {
    int amount = 0;

    for (auto i : b) {
      if (i == v) {
        amount++;
      }
    }

    return amount;
  };

  int result = 0;
  std::map<int, int> cache;
  for (auto i : a) {
    if (cache.find(i) == cache.end()) {
      cache[i] = count(i);
    }

    result += i * cache[i];
  }

  std::cout << result << '\n';

  return 0;
}

