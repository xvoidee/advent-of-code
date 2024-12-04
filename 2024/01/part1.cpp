#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
  std::ifstream f("input.txt");

  int x, y;

  std::vector<int> a, b;

  while (f >> x >> y) {
    a.push_back(x);
    b.push_back(y);
  }

  std::sort(a.begin(), a.end());
  std::sort(b.begin(), b.end());

  int sum = 0;

  for (int i = 0; i < a.size(); ++i) {
    sum += std::abs(a[i] - b[i]);
  }

  std::cout << sum << '\n';

  return 0;
}

