//
// Created by Theotime Poisseau on 06/12/2025.
//

#include "day_06.h"

#include <string>
#include <fstream>
#include <iostream>
#include <mdspan>
#include <sstream>
#include <regex>
#include <vector>

using namespace std;

enum ParseMode {
    NUMBER,
    NUMBER_WS_SKIP,
    OPERATION,
};

void day_06_part_1_2025() {
    ifstream input(filesystem::current_path().append("2025/inputs/day_06.txt"));
    if (!input.is_open()) throw runtime_error("Unable to open file");

    // string line;
    // while (getline(input, line, ' ')) {
    //     cout << line << endl;
    // }

    vector<unsigned long> raw_matrix;
    size_t columns = 0;
    size_t rows = 0;
    vector<char> operations;

    {
        ParseMode parse_mode = NUMBER;
        bool first_line = true;
        stringstream ss;
        char ch;
        while (input >> noskipws >> ch) {
            if (parse_mode == NUMBER) {
                if (ch >= '0' && ch <= '9') {
                    ss << ch;
                    continue;
                }
                if (ch == '+' || ch == '*') {
                    operations.push_back(ch);
                    parse_mode = OPERATION;
                    continue;
                }

                string number_str = ss.str();
                if (!number_str.empty()) {
                    raw_matrix.push_back(stoul(ss.str()));
                    ss = stringstream();

                    if (first_line) columns++;
                }

                if (ch == '\n') {
                    rows++;
                    first_line = false;
                }
                if (ch == ' ') parse_mode = NUMBER_WS_SKIP;
            } else if (parse_mode == NUMBER_WS_SKIP) {
                if (ch >= '0' && ch <= '9') {
                    ss << ch;
                    parse_mode = NUMBER;
                } else if (ch == '\n') {
                    rows++;
                    first_line = false;
                    parse_mode = NUMBER;
                }
            } else if (parse_mode == OPERATION) {
                if (ch == '+' || ch == '*') {
                    operations.push_back(ch);
                }

                if (ch == '\n') {
                    break;
                }
            }
        }
    }

    auto matrix = mdspan(raw_matrix.data(), rows, columns);

    cout << format("Matrix rows: {}, columns: {}", rows, columns) << endl;

    uint64_t total = 0;
    for (size_t col_index = 0; col_index < operations.size(); col_index++) {
        auto operation = operations[col_index];
        uint64_t operation_total;

        cout << format("{}", operation);
        if (operation == '+') {
            operation_total = 0;
            for (size_t row_index = 0; row_index < rows; row_index++) {
                auto value = matrix[row_index, col_index];
                operation_total += value;

                cout << " " << value;
            }
        } else if (operation == '*') {
            operation_total = 1;
            for (size_t row_index = 0; row_index < rows; row_index++) {
                auto value = matrix[row_index, col_index];
                operation_total *= value;

                cout << " " << value;
            }
        }
        cout << format(" => {}", operation_total) << endl;
        total += operation_total;
    }

    cout << "Total: " << total << endl;
}

void day_06_part_2_2025() {
}
