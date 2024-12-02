#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

bool is_safe(const std::vector<int> & v)
{
	bool asc;
	bool valid = true;
	int  index = -1;

	int previous = 0;

	for (int value : v) {
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

	return valid;
}

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

		int value;
		std::vector<int> v;

		v.clear();
		while (ss >> value) {
			v.push_back(value);
		}

		bool safe = false;

		for (int i = 0; i < v.size(); ++i) {
			auto copy = v;
			copy.erase(copy.begin() + i);
			safe |= is_safe(copy);
		}

		if (safe) {
			amount++;
		}
	}

	std::cout << amount << '\n';

	return 0;
}

