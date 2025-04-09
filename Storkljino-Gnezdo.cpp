#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <tuple>
#include <string>
#include <set>
#include <algorithm>
#include <chrono>

// constant file name
const std::string FILENAME_INPUT = "testni_primer2.txt";
const std::string FILENAME_OUTPUT = "testni_primer1_moje_r.txt";

int main() {
    std::ifstream file_in(FILENAME_INPUT);
    std::ofstream file_out(FILENAME_OUTPUT);

    if (!file_in.is_open()) {
        std::cerr << "Failed to open " << FILENAME_INPUT << "\n";
        return 1;
    }

    std::string line;
    std::getline(file_in, line);
    if (line.empty()) return 1;

    auto start = std::chrono::high_resolution_clock::now();

    std::istringstream iss(line);
    int n, v, s;
    iss >> n >> v >> s;

    std::vector<std::tuple<int, int, int>> changes;
    std::vector<std::multiset<int>> msVec(s);

    // Initialize the multiset for every column (width columns)
    for (int i = 0; i < s; i++) {
        std::multiset<int> ms = {};
		msVec[i] = ms;
    }

    for (int i = 0; i < n; i++) {
        std::getline(file_in, line);
        std::istringstream iss(line);

        char c;
        iss >> c;

        if (c == '+') {
            int y, x, d;
            iss >> y >> x >> d;

            auto t = std::make_tuple(y, x, d);
            changes.push_back(t);

            for (int j = x; j < x + d; j++) {
                msVec[j].insert(y);
            }
        }
        else if (c == '-') {
            int idx;
            iss >> idx;

			auto [y, x, d] = changes[idx - 1];

			// Check if it has been removed
            //if (y != 0) {
				// Remove every entry from the multiset
                for (int j = x; j < x + d; j++) {
                    auto it = msVec[j].find(y);
                    if (it != msVec[j].end()) {
                        msVec[j].erase(it);
                    }
					else {
						std::cerr << "Error: Attempting to remove a non-existing entry from the multiset.\n";
						return 1;
					}
                }
            //}
            
			// changes[idx - 1] = std::make_tuple(0, 0, 0);  // Mark as removed

			// access first item from tuple of changes[j - 1]
            //std::get<0>(changes[idx - 1]) = 0;
        }
        else {
            std::cerr << "Invalid operation format at line " << i + 1 << "\n";
            return 1;
        }

        int smallest = std::numeric_limits<int>::min();  // Initialize to the largest possible value

        // Iterate through all the multisets in msVec
        for (int j = 0; j < s; j++) {
            if (msVec[j].empty()) {
                smallest = v;  // Set smallest to v if any multiset is empty
                break;
            }

            int min_in_set = *msVec[j].begin();  // begin() gives the smallest element
            smallest = std::max(smallest, min_in_set);  // Update smallest if needed
        }

        //std::cout << smallest << std::endl;
		if (i == n - 1) {
			file_out << smallest;
		}
		else {
			file_out << smallest << std::endl;
		}
    }

	file_in.close();
	file_out.close();

    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duration = end - start;
    std::cout << "Elapsed time: " << duration.count() << " seconds" << std::endl;

    return 0;
}
