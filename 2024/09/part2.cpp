#include <fstream>
#include <iostream>
#include <string>
#include <vector>

struct Chunk {
  int length = 0;
  int id     = -1;

  bool isEmpty() const {
    return id == -1;
  }

  bool isFile() const {
    return !isEmpty();
  }
};

int main()
{
  std::fstream f("input.txt");
  std::string l;

  f >> l;

  std::vector<Chunk> chunks;

  auto at = [&] (int i) -> int {
    return l[i] - '0';
  };

  for (int i = 0; i < l.size(); ++i) {
    const int length = at(i);

    if (length == 0) {
      continue;
    }

    chunks.push_back({length, ((i % 2) == 0) ? (i / 2) : -1});
  }

  for (int from = chunks.size() - 1; from >= 2; --from) {
    if (chunks[from].isEmpty()) {
      continue;
    }

    for (int to = 1; to <= from - 1; ++to) {
      if (chunks[to].isFile()) {
        continue;
      }

      if (chunks[to].length == chunks[from].length) {
        chunks[to  ]    = chunks[from];
        chunks[from].id = -1;

        break;
      } else if (chunks[to].length > chunks[from].length) {
        chunks.insert(chunks.begin() + to, chunks[from]);

        to   += 1;
        from += 1;

        chunks[from].id      = -1;
        chunks[to  ].length -= chunks[from].length;

        break;
      }
    }
  }

  long long checksum_value   = 0;
  long long checksum_pointer = 0;

  for (int i = 0; i < chunks.size(); ++i) {
    for (int j = 0; j < chunks[i].length; ++j) {
      if (chunks[i].isFile()) {
        checksum_value += checksum_pointer * chunks[i].id;
      }
      checksum_pointer += 1;
    }
  }

  std::cout << checksum_value << '\n';

  return 0;
}

