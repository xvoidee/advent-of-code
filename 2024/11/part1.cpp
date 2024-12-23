#include <fstream>
#include <iostream>
#include <functional>
#include <map>

struct Stone {
  long number = 0;
  long level  = 0;

  bool operator < (const Stone & b) const {
    if (number < b.number) {
      return true;
    }

    if (number > b.number) {
      return false;
    }

    return level < b.level;
  }
};

int main()
{
  std::ifstream f("input.txt");

  std::map<Stone, long> cache;

  std::function<long(long, long)> divide;
  divide = [&] (long number, long level) -> long {
    if (level == 25) {
      return 1;
    }

    const Stone stone = {number, level};
    auto it = cache.find(stone);
    if (it != cache.end()) {
      return it->second;
    }

    long t = 0;

    for (;;) {
      if (number == 0) {
        t = divide(1, level + 1);
        break;
      }

      const auto s = std::to_string(number);
      const auto l = s.size();
      if ((l % 2) == 0) {
        t =
          divide(std::stoi(s.substr(0, l / 2)), level + 1) +
          divide(std::stoi(s.substr(l / 2   )), level + 1);
        break;
      }

      t = divide(number * 2024, level + 1);
      break;
    }

    cache[stone] = t;
    return t;
  };

  long amount = 0;
  long value  = 0;
  while (f >> value) {
    amount += divide(value, 0);
  }

  std::cout << amount << '\n';

  return 0;
}

