#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <tuple>
#include <string>
#include <set>

//constant file name
const std::string FILENAME = "testni_primer1.txt";

int main()
{
	std::ifstream file(FILENAME);

	// Check if the file opened successfully
    if (!file.is_open()) {
        std::cerr << "Failed to open file.txt\n";
        return 1;
    }

	// Read the first line and check if it is empty
	std::string line;
    std::getline(file, line);
	if (line.empty()) return 1;

	// Read the first line and save the values
    std::istringstream iss(line);
	int n, v, s; // n - number of changes, v - height/višina, s - width/širina
	iss >> n >> v >> s;
	//std::cout << v << " " << s << " " << n << "\n";

	int x = 0, y = 0, d = 0;
	char c; // check if + or -
	std::vector<std::tuple<int, int, int>> changes;
	// make a multiset called ms
	std::multiset<int> ms;
	for (int i = 0; i < n; i++) {
		std::getline(file, line);
		std::istringstream iss(line);
		iss >> c;
		if (c == '+') {
			iss >> x >> y >> d;
            std::tuple<int, int, int> ch = std::make_tuple(x, y, d);
			changes.push_back(ch);

			// Insert the values into the multiset
			for (int j = x; j < d + 1; j++) {
				ms.insert(y);
			}
		}
		else if (c == '-') {
			iss >> x;
			changes[x - 1] = std::make_tuple(0, 0, 0);

			// Remove the values from the multiset
			for (int j = x; j < d + 1; j++) {
				auto it = ms.find(y);
				if (it != ms.end()) {
					ms.erase(it);
				}
				else {
					std::cerr << "Invalid change format\n";
					return 1;
				}
			}
		}
		else {
			std::cerr << "Invalid change format\n";
			return 1;
		}
		//std::cout << i << " " << c << " " << x << " " << y << " " << d << "\n";


	}

	// Print out all the changes
	for (int i = 0; i < changes.size(); i++) {
		std::cout << std::get<0>(changes[i]) << " " << std::get<1>(changes[i]) << " " << std::get<2>(changes[i]) << "\n";
	}
}