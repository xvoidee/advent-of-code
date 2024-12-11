#include <fstream>
#include <vector>
#include <iostream>
#include <sstream>

bool is_valid(const std::vector<long> & values, long value, int i)
{
  if (i == 0) {
    return values[0] == value;
  }

  bool result = false;
  long last   = values[i];

  if ((value % last) == 0) {
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

