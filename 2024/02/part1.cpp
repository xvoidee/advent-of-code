#include <fstream>
#include <sstream>
#include <iostream>

int main()
{
  std::ifstream f("input.txt");

  char buf[32];
  int  amount = 0;
  while (f.getline(buf, 32)) {
    std::stringstream ss(buf);

    if (ss.str().empty()) {
      break;
    }

    int index    = -1;
    int value    = 0;
    int previous = 0;
    bool asc     = true;
    bool valid   = true;

    while (ss >> value) {
      index++;

      if (index == 0) {
        previous = value;
        continue;
      }

      if ((value == previous) || (std::abs(value - previous) > 3)) {
        valid = false;
        break;
      }

      if (index == 1) {
        asc = value > previous;
        previous = value;
        continue;
      }

      if (asc) {
        if (previous > value) {
          valid = false;
          break;
        }
      } else {
        if (previous < value) {
          valid = false;
          break;
        }
      }

      previous = value;
    }

    if (valid) {
      amount++;
    }
  }

  std::cout << amount << '\n';

  return 0;
}

