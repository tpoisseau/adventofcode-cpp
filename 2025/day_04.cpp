//
// Created by Theotime Poisseau on 04/12/2025.
//

#include "day_04.h"

#include <string>
#include <fstream>
#include <iostream>
#include <mdspan>
#include <vector>
#include <ranges>

using namespace std;

vector<pair<size_t, size_t> > get_neighbors(
    const size_t row, const size_t column,
    const size_t row_size, const size_t column_size
) {
    const bool is_top_border = row == 0;
    const bool is_bottom_border = row == row_size - 1;
    const bool is_left_border = column == 0;
    const bool is_right_border = column == column_size - 1;

    vector<pair<size_t, size_t> > neighbors;
    if (!is_top_border) {
        if (!is_left_border) neighbors.emplace_back(row - 1, column - 1);
        neighbors.emplace_back(row - 1, column);
        if (!is_right_border) neighbors.emplace_back(row - 1, column + 1);
    }
    if (!is_right_border) {
        neighbors.emplace_back(row, column + 1);
        if (!is_bottom_border) neighbors.emplace_back(row + 1, column + 1);
    }
    if (!is_bottom_border) {
        neighbors.emplace_back(row + 1, column);
        if (!is_left_border) neighbors.emplace_back(row + 1, column - 1);
    }
    if (!is_left_border) neighbors.emplace_back(row, column - 1);

    return neighbors;
}

void day_04_part_1_2025() {
    size_t row_size = 0;
    size_t column_size = 0;
    vector<char> raw_grid;

    {
        ifstream input(filesystem::current_path().append("2025/inputs/day_04.txt"));
        if (!input.is_open()) throw runtime_error("Unable to open file");

        string line;
        while (getline(input, line)) {
            if (line.empty()) break;

            constexpr std::identity identity_char;
            ranges::transform(line, std::back_inserter(raw_grid), identity_char);

            column_size = line.size();
            row_size++;
        }
    }

    const auto grid = mdspan(raw_grid.data(), row_size, column_size);

    uint64_t accessible_paper_tolls = 0;
    for (const auto row: views::iota(0uz, row_size)) {
        for (const auto column: views::iota(0uz, column_size)) {
            const auto cell = grid[row, column];
            if (cell != '@') {
                cout << cell;
                continue;
            }

            u_short paper_tolls_count = 0;
            for (auto &[neighbor_row, neighbor_column]: get_neighbors(row, column, row_size, column_size)) {
                if (paper_tolls_count >= 4) break;
                const auto neighbor_cell = grid[neighbor_row, neighbor_column];
                if (neighbor_cell != '@') continue;

                paper_tolls_count++;
            }

            if (paper_tolls_count >= 4) {
                cout << cell;
                continue;
            }

            accessible_paper_tolls++;
            cout << "✔";
        }
        cout << endl;
    }
    cout << format("Accessible paper tolls: {}", accessible_paper_tolls) << endl;
}

void day_04_part_2_2025() {
    size_t row_size = 0;
    size_t column_size = 0;
    vector<char> raw_grid;

    {
        ifstream input(filesystem::current_path().append("2025/inputs/day_04.txt"));
        if (!input.is_open()) throw runtime_error("Unable to open file");

        string line;
        while (getline(input, line)) {
            if (line.empty()) break;

            constexpr std::identity identity_char;
            ranges::transform(line, std::back_inserter(raw_grid), identity_char);

            column_size = line.size();
            row_size++;
        }
    }

    const auto grid = mdspan(raw_grid.data(), row_size, column_size);

    uint64_t sum_accessible_paper_tolls = 0;
    uint64_t steps = 0;
    while (true) {
        steps++;
        vector<pair<size_t, size_t> > paper_tolls_to_remove;
        for (const auto row: views::iota(0uz, row_size)) {
            for (const auto column: views::iota(0uz, column_size)) {
                const auto cell = grid[row, column];
                if (cell != '@') {
                    cout << cell;
                    continue;
                }

                u_short paper_tolls_count = 0;
                for (auto &[neighbor_row, neighbor_column]: get_neighbors(row, column, row_size, column_size)) {
                    if (paper_tolls_count >= 4) break;
                    const auto neighbor_cell = grid[neighbor_row, neighbor_column];
                    if (neighbor_cell != '@') continue;

                    paper_tolls_count++;
                }

                if (paper_tolls_count >= 4) {
                    cout << cell;
                    continue;
                }

                paper_tolls_to_remove.emplace_back(row, column);
                cout << "✔";
            }
            cout << endl;
        }

        const auto accessible_paper_tolls = paper_tolls_to_remove.size();
        cout << format("Accessible paper tolls: {}", accessible_paper_tolls) << endl;
        if (accessible_paper_tolls == 0) break;

        for (const auto &[row, column]: paper_tolls_to_remove) {
            grid[row, column] = '.';
        }

        sum_accessible_paper_tolls += accessible_paper_tolls;
    }

    cout << format("Total accessible paper tolls: {}, in {} steps", sum_accessible_paper_tolls, steps) << endl;
}
