#include <fstream>
#include <vector>
#include <iostream>
#include <sstream>

static_assert(sizeof(long) == 8, "long data type is not 8 bytes");

long divider(const long v)
{
  const long factors[18] = {
    10LL,
    100LL,
    1000LL,
    10000LL,
    100000LL,
    1000000LL,
    10000000LL,
    100000000LL,
    1000000000LL,
    10000000000LL,
    100000000000LL,
    1000000000000LL,
    10000000000000LL,
    100000000000000LL,
    1000000000000000LL,
    10000000000000000LL,
    100000000000000000LL,
    1000000000000000000LL,
  };

  for (int i = 0; i < 18; ++i) {
    if (v < factors[i]) {
      return factors[i];
    }
  }

  return 0;
}

bool is_valid(const std::vector<long> values, long value, int i)
{
  if (i == 0) {
    return values[0] == value;
  }

  bool result = false;
  long last   = values[i];

  if (((value - last) % divider(last)) == 0) {
    result = result || is_valid(values, (value - last) / divider(last), i - 1);
  }

  if (!result && (value % last) == 0) {
    result = result || is_valid(values, value / last, i - 1);
  }

  if (!result) {
    result = result || is_valid(values, value - last, i - 1);
  }

  return result;
}

int main()
{
  std::fstream f("input.txt");
  std::string l;

  long sum = 0;

  while (getline(f, l)) {
    std::istringstream ss(l + '\n');

    long target;
    long value;

    std::vector<long> values;

    {
      char unused;
      ss >> target >> unused;
      value = target;

      long n;
      while (ss >> n) {
        values.push_back(n);
      }
    }

    if (is_valid(values, value, values.size() - 1)) {
      sum += target;
    }
  }

  std::cout << sum << '\n';

  return 0;
}

