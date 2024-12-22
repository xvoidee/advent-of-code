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

void dbg(const Chunk & c, int padding)
{
  std::string s;
  s.reserve(16);

  for (int i = 0; i < c.length; ++i) {
    if (c.isEmpty()) {
      s += '.';
    } else {
      s += std::to_string(c.id);
    }
  }

  if (padding != 0) {
    printf("%*s", padding, s.c_str());
  } else {
    printf("%s", s.c_str());
  }
}

void dbg(const std::vector<Chunk> & chunks)
{
  for (auto c : chunks) {
    dbg(c, 0);
  }
}

int main()
{
  std::fstream f("input.txt");
  std::string l;

  f >> l;
//  l = "2333133121414131402";

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

  for (int i = chunks.size() - 1; i >= 2; --i) {
    auto from = chunks[i];
    if (from.isEmpty()) {
      continue;
    }

    for (int j = 1; j < i - 1; ++j) {
      auto to = chunks[j];
      if (to.isFile()) {
        continue;
      }

      if (to.length == from.length) {
        chunks[j]    = chunks[i];
        chunks[i].id = -1;

        break;
      } else if (to.length > from.length) {
        chunks.insert(chunks.begin() + j, from);

        i += 1;
        j += 1;

        chunks[i].id      = -1;
        chunks[j].length -= from.length;

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

