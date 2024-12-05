#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>

int main()
{
  std::fstream f("input.txt");
  std::string l;

  int sum = 0;

  bool parse_rules   = true;
  bool parse_updates = false;

  std::vector<std::pair<int, int>> rules;

  auto is_valid_update = [&rules] (const std::vector<int> & update) {
    for (int i = 0; i < update.size() - 1; ++i) {
      for (int j = i + 1; j < update.size(); ++j) {
        for (int k = 0; k < rules.size(); ++k) {
          if ((rules[k].first == update[j]) && (rules[k].second == update[i])) {
            return false;
          }
        }
      }
    }

    return true;
  };

  while (getline(f, l)) {
    if (l.empty()) {
      parse_rules   = false;
      parse_updates = true;
      continue;
    }

    if (parse_rules) {
      std::stringstream ss(l);
      int a, b;
      char d;
      ss >> a >> d >> b;
      rules.push_back({a, b});
      continue;
    }

    if (parse_updates) {
      std::stringstream ss(l);
      int n;

      std::vector<int> update;
      while (ss >> n) {
        update.push_back(n);
        if (ss.peek() == ',') {
          ss.ignore();
        }
      }
      if (is_valid_update(update)) {
        sum += update[update.size() / 2];
      }
      continue;
    }
  }

  std::cout << sum << '\n';

  return 0;
}

