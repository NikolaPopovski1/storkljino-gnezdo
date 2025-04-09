#include <iostream>
#include <cstdio>
#include <sstream>
#include <vector>
#include <tuple>
#include <string>
#include <set>
#include <algorithm>
#include <chrono>

// constant file name
//const std::string FILENAME_INPUT = "testni_primer2.txt";
//const std::string FILENAME_OUTPUT = "testni_primer1_moje_r.txt";

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: program.exe <input_filename>\n";
        return 1;
    }
    const std::string FILENAME_INPUT = argv[1];

    FILE* file;
    if (fopen_s(&file, FILENAME_INPUT.c_str(), "r") != 0 || !file) {
        std::cerr << "Failed to open file\n";
        return 1;
    }

    //auto start_total = std::chrono::high_resolution_clock::now();
    //auto time_insert = std::chrono::nanoseconds(0);
    //auto time_erase = std::chrono::nanoseconds(0);
    //auto time_min_scan = std::chrono::nanoseconds(0);

    int n, v, s;
    fscanf_s(file, "%d %d %d\n", &n, &v, &s);

    std::vector<std::tuple<int, int, int>> changes;
    std::vector<std::multiset<int>> msVec(s, std::multiset<int>{v});

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < n; i++) {
        char c;
        fscanf_s(file, " %c", &c);

        if (c == '+') {
            int y, x, d;
            fscanf_s(file, "%d %d %d\n", &y, &x, &d);
            changes.emplace_back(y, x, d);

            //auto insert_start = std::chrono::high_resolution_clock::now();
            for (int j = x; j < x + d; j++) {
                msVec[j].insert(y);
            }
            //time_insert += std::chrono::high_resolution_clock::now() - insert_start;
        }
        else if (c == '-') {
            int idx;
            fscanf_s(file, "%d\n", &idx);
            auto [y, x, d] = changes[idx - 1];

			// Remove every entry from the multiset
            //auto erase_start = std::chrono::high_resolution_clock::now();
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
            //time_erase += std::chrono::high_resolution_clock::now() - erase_start;
        }
        else {
            std::cerr << "Invalid operation format at line " << i + 1 << "\n";
            return 1;
        }

        int smallest = std::numeric_limits<int>::min();  // Initialize to the largest possible value

        // Iterate through all the multisets in msVec
        //auto min_scan_start = std::chrono::high_resolution_clock::now();
        for (int j = 0; j < s; j++) {
            int min_in_set = *msVec[j].begin();
            smallest = std::max(smallest, min_in_set);
        }
        //time_min_scan += std::chrono::high_resolution_clock::now() - min_scan_start;

        std::cout <<  smallest << std::endl;
    }

    fclose(file);
	//file_out.close();

    //auto end = std::chrono::high_resolution_clock::now();

    //std::chrono::duration<double> duration = end - start;
    //std::cout << "Elapsed time: " << duration.count() << " seconds" << std::endl;
    //std::cout << "Insert time: " << std::chrono::duration<double>(time_insert).count() << " s" << std::endl;
    //std::cout << "Erase time:  " << std::chrono::duration<double>(time_erase).count() << " s" << std::endl;
    //std::cout << "Min-scan time: " << std::chrono::duration<double>(time_min_scan).count() << " s" << std::endl;

    return 0;
}
