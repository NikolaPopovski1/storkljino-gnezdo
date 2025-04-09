#include <iostream>
#include <fstream>
#include <sstream>

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
	std::cout << v << " " << s << " " << n << "\n";

	int x = 0, y = 0, d = 0;
	char c; // check if + or -
	for (int i = 0; i < n; i++) {
		std::getline(file, line);
		std::istringstream iss(line);

		iss >> c;
		if (c == '+') {
			iss >> x >> y >> d;
		}
		else if (c == '-') {
			iss >> x;
		}
		else {
			std::cerr << "Invalid change format\n";
		}
		std::cout << i << " " << c << " " << x << " " << y << " " << d << "\n";
	}
}