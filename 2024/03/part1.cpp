#include <regex>
#include <iostream>
#include <fstream>
#include <string>

int main()
{
  std::ifstream f("input.txt");
  std::string s;

  int result = 0;

  while (f >> s) {
    std::regex r("mul\\((\\d+)\\,(\\d+)\\)");

    auto begin = std::sregex_iterator(s.begin(), s.end(), r);
    auto end   = std::sregex_iterator();

    for (auto i = begin; i != end; ++i) {
      std::smatch match = *i;
      std::string match_str = match.str();

      result += std::stoi(match[1]) * std::stoi(match[2]);
    }
  }

  std::cout << result << std::endl;

	return 0;
}

