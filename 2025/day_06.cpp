//
// Created by Theotime Poisseau on 06/12/2025.
//

#include "day_06.h"

#include <string>
#include <fstream>
#include <iostream>
#include <list>
#include <mdspan>
#include <numeric>
#include <sstream>
#include <regex>
#include <vector>

#include "../shared/iterators.h"

using namespace std;

enum ParseMode {
    NUMBER,
    NUMBER_WS_SKIP,
    OPERATION,
};

void day_06_part_1_2025() {
    ifstream input(filesystem::current_path().append("2025/inputs/day_06.txt"));
    if (!input.is_open()) throw runtime_error("Unable to open file");

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
    ifstream input(filesystem::current_path().append("2025/inputs/day_06.txt"));
    if (!input.is_open()) throw runtime_error("Unable to open file");

    vector<char> raw_matrix;
    size_t columns = 0;
    size_t rows = 0;

    string line;
    while (getline(input, line)) {
        if (line.empty()) break;

        const auto line_length = line.size();
        if (line_length > columns) columns = line_length;

        raw_matrix.insert(raw_matrix.end(), line.begin(), line.end());
        rows++;
    }

    const auto matrix = mdspan(raw_matrix.data(), rows, columns);
    stringstream ss;
    list<unsigned long> numbers_to_operate;
    uint64_t total = 0;
    for (auto [column, _]: aoc::iterators::matrix_horizontal_reverse_it(matrix, 0, columns, 1)) {
        char operation = '\0';
        for (auto row_entry: aoc::iterators::matrix_vertical_it(matrix, column, 0)) {
            auto [row, ch] = row_entry;
            if (ch >= '0' && ch <= '9') {
                ss << static_cast<char>(ch);
                continue;
            }
            if (ch != ' ') operation = ch;
        }

        string ss_str = ss.str();
        ss = stringstream();
        if (ss_str.empty()) continue;

        auto value = stoul(ss_str);
        numbers_to_operate.push_back(value);

        if (operation == '+') {
            uint64_t sum = 0;
            for (auto number: numbers_to_operate) {
                sum += number;
            }
            total += sum;

            numbers_to_operate = {};
        } else if (operation == '*') {
            uint64_t sum = 1;
            for (auto number: numbers_to_operate) {
                sum *= number;
            }
            total += sum;

            numbers_to_operate = {};
        }
    }

    cout << "Total: " << total << endl;
}
