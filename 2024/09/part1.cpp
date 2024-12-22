#include <fstream>
#include <iostream>
#include <string>

int main()
{
  std::fstream f("input.txt");
  std::string l;

  f >> l;

  int to   = 0;
  int from = l.size();

  int free_blocks = 0;
  int file_blocks = 0;

  long checksum_value   = 0;
  long checksum_pointer = 0;

  auto at = [&] (int i) -> int {
    return l[i] - '0';
  };

  auto id = [&] (int i) -> int {
    return i / 2;
  };

  auto is_free = [&] (int i) -> bool {
    return (i % 2) == 1;
  };

  auto is_file = [&] (int i) -> bool {
    return (i % 2) == 0;
  };

  auto what = [&] (int i) -> char {
    if (is_free(i)) {
      return 'E';
    }

    return 'F';
  };

  while (from > to) {
    if (is_file(to)) {
      for (int i = 0; i < at(to); ++i) {
        checksum_value   += checksum_pointer * id(to);
        checksum_pointer += 1;
      }

      ++to;
      free_blocks = at(to);
      continue;
    } else {
      if (free_blocks == 0) {
        ++to;
        continue;
      }
    }

    if (is_free(from) || (from == l.size())) {
      --from;
      file_blocks = at(from);
      continue;
    } else {
      if (file_blocks == 0) {
        --from;
        continue;
      }
    }

    checksum_value   += checksum_pointer * id(from);
    checksum_pointer += 1;

    --free_blocks;
    --file_blocks;
  }

  for (int i = 0; i < file_blocks; ++i) {
    checksum_value   += checksum_pointer * id(from);
    checksum_pointer += 1;
  }

  std::cout << checksum_value << '\n';

  return 0;
}

