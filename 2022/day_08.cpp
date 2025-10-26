//
// Created by Theotime Poisseau on 11/10/2025.
// https://adventofcode.com/2022/day/8
//

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include <mdspan>
#include <ranges>
#include <tuple>
#include <algorithm>

#include "../shared/iterators.h"

#include "day_08.h"

using namespace std;
using namespace aoc::iterators;

u_short char_to_short(const char c) {
    return static_cast<u_short>(c - '0')
           + 1; // hacky tree size +1 so tree with 0 size can be marked visible ^^
}

void day_08_part_1() {
    vector<vector<u_short> > forest;

    {
        ifstream input(filesystem::current_path().append("2022/inputs/day_08.txt"));
        if (!input.is_open()) throw runtime_error("Unable to open file");

        string line;
        while (getline(input, line)) {
            vector<u_short> row;
            ranges::transform(line, std::back_inserter(row), char_to_short);
            forest.push_back(row);
        }
    }

    // tuple left is a row coordinate, tuple right is a column coordinate;
    map<tuple<size_t, size_t>, u_short> visible_trees{};

    for (size_t row = 0; row < forest.size(); row++) {
        auto forest_row = forest[row];

        // check left to right
        {
            u_short max_tree_size = 0;
            for (size_t column = 0; column < forest_row.size(); column++) {
                const auto tree_size = forest_row[column];
                if (tree_size <= max_tree_size) continue;

                max_tree_size = tree_size;
                visible_trees[make_tuple(row, column)] = tree_size;
            }
        }

        // check right to left
        {
            u_short max_tree_size = 0;
            size_t column = forest_row.size() - 1;
            for (auto it = forest_row.rbegin(); it != forest_row.rend(); ++it, column--) {
                const auto tree_size = forest_row[column];
                if (tree_size <= max_tree_size) continue;

                max_tree_size = tree_size;
                visible_trees[make_tuple(row, column)] = tree_size;
            }
        }
    }

    size_t column_size = forest[0].size();
    for (size_t column = 0; column < column_size; column++) {
        // check top to bottom
        {
            u_short max_tree_size = 0;
            for (size_t row = 0; row < forest.size(); row++) {
                const auto tree_size = forest[row][column];
                if (tree_size <= max_tree_size) continue;

                max_tree_size = tree_size;
                visible_trees[make_tuple(row, column)] = tree_size;
            }
        }

        // check bottom to top
        {
            u_short max_tree_size = 0;
            size_t row = forest.size() - 1;
            for (auto it = forest.rbegin(); it != forest.rend(); ++it, row--) {
                const auto tree_size = (*it)[column];
                if (tree_size <= max_tree_size) continue;

                max_tree_size = tree_size;
                visible_trees[make_tuple(row, column)] = tree_size;
            }
        }
    }


    for (const auto &[coordinate, tree_size]: visible_trees) {
        const auto [row, column] = coordinate;
        cout << "Tree at (" << row << ", " << column << ") with size: " << tree_size << endl;
    }

    cout << "Total visible trees: " << visible_trees.size() << endl;
}

void day_08_part_2() {
    vector<vector<u_short> > forest;

    {
        ifstream input(filesystem::current_path().append("2022/inputs/day_08.txt"));
        if (!input.is_open()) throw runtime_error("Unable to open file");

        string line;
        while (getline(input, line)) {
            vector<u_short> row;
            ranges::transform(line, std::back_inserter(row), char_to_short);
            forest.push_back(row);
        }
    }

    const auto column_size = forest.size();

    u_int64_t max_scenic_score = 0;
    for (size_t row = 0; row < column_size; row++) {
        auto row_long = static_cast<long>(row);
        auto &forest_row = forest[row];
        const auto row_size = forest_row.size();

        for (size_t column = 0; column < row_size; column++) {
            auto column_long = static_cast<long>(column);
            auto tree_size = forest_row[column];

            // check left to right
            u_int64_t looking_right_scenic_score = 0;
            for (size_t cursor_column = column + 1; cursor_column < row_size; cursor_column++) {
                const auto view_tree_size = forest_row[cursor_column];
                looking_right_scenic_score++;
                if (view_tree_size >= tree_size) break;
            }

            // check right to left
            u_int64_t looking_left_scenic_score = 0;
            for (auto cursor_column = column_long - 1; cursor_column >= 0; cursor_column--) {
                const auto view_tree_size = forest_row[cursor_column];
                looking_left_scenic_score++;
                if (view_tree_size >= tree_size) break;
            }

            // check top to bottom
            u_int64_t looking_down_scenic_score = 0;
            for (size_t cursor_row = row + 1; cursor_row < column_size; cursor_row++) {
                const auto view_tree_size = forest[cursor_row][column];
                looking_down_scenic_score++;
                if (view_tree_size >= tree_size) break;
            }

            // check bottom_to_top
            u_int64_t looking_up_scenic_score = 0;
            for (long cursor_row = row_long - 1; cursor_row >= 0; cursor_row--) {
                const auto view_tree_size = forest[cursor_row][column];
                looking_up_scenic_score++;
                if (view_tree_size >= tree_size) break;
            }

            u_int64_t scenic_score = looking_right_scenic_score * looking_left_scenic_score *
                                     looking_down_scenic_score * looking_up_scenic_score;


            cout << "Scenic score for tree at (" << row << ", " << column << "): " << scenic_score << " ";
            cout << "Looking right: " << looking_right_scenic_score << ", looking left: " << looking_left_scenic_score;
            cout << ", looking down: " << looking_down_scenic_score << ", looking up: " << looking_up_scenic_score <<
                    endl;

            if (scenic_score > max_scenic_score) max_scenic_score = scenic_score;
        }
    }

    cout << endl;
    cout << "Max scenic score: " << max_scenic_score << endl;
}

void day_08_part_2_matrix() {
    vector<u_short> raw_forest_data;

    size_t row_size = 0;
    size_t column_size = 0;
    {
        ifstream input(filesystem::current_path().append("2022/inputs/day_08.txt"));
        if (!input.is_open()) throw runtime_error("Unable to open file");

        string line;
        while (getline(input, line)) {
            row_size++;
            ranges::transform(line, std::back_inserter(raw_forest_data), char_to_short);
        }
        column_size = line.size();
    }

    const auto matrix = mdspan(raw_forest_data.data(), row_size, column_size);

    u_int64_t max_scenic_score = 0;
    for (const auto row: views::iota(0uz, row_size)) {
        const auto row_next = row + 1;

        for (const auto column: views::iota(0uz, column_size)) {
            const auto tree = matrix[row, column];
            const auto column_next = column + 1;

            // check left to right
            u_int64_t looking_right_scenic_score = 0uz;
            for (auto [column_view, tree_view]: matrix_horizontal_it(matrix, row, column_next)) {
                looking_right_scenic_score++;
                if (tree_view >= tree) break;
            }

            // check right to left
            u_int64_t looking_left_scenic_score = 0uz;
            if (row == 0 && column == 3) {
                vector<string> debug;
                auto it = matrix_horizontal_reverse_it(matrix, row, column, 1);
                for (auto [column_view, tree_view]: it) {
                    debug.push_back(std::format("<{}, {}>", column_view, tree_view));
                }
                cout << "";
            }
            for (auto [column_view, tree_view]: matrix_horizontal_reverse_it(matrix, row, column, 1)) {
                looking_left_scenic_score++;
                if (tree_view >= tree) break;
            }

            // check top to bottom
            u_int64_t looking_down_scenic_score = 0uz;
            for (auto [row_view, tree_view]: matrix_vertical_it(matrix, column, row_next)) {
                looking_down_scenic_score++;
                if (tree_view >= tree) break;
            }

            // check bottom to top
            u_int64_t looking_up_scenic_score = 0uz;
            for (auto [row_view, tree_view]: matrix_vertical_reverse_it(matrix, column, row, 1)) {
                looking_up_scenic_score++;
                if (tree_view >= tree) break;
            }

            u_int64_t scenic_score = looking_right_scenic_score * looking_left_scenic_score *
                                     looking_down_scenic_score * looking_up_scenic_score;

            cout << "Scenic score for tree at (" << row << ", " << column << "): " << scenic_score << " ";
            cout << "Looking right: " << looking_right_scenic_score << ", looking left: " << looking_left_scenic_score;
            cout << ", looking down: " << looking_down_scenic_score << ", looking up: " << looking_up_scenic_score <<
                    endl;

            if (scenic_score > max_scenic_score) max_scenic_score = scenic_score;
        }
    }

    cout << endl;
    cout << "Max scenic score: " << max_scenic_score << endl;
}
