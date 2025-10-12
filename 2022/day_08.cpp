//
// Created by Theotime Poisseau on 11/10/2025.
// https://adventofcode.com/2022/day/8
//

#include <string>
#include <fstream>
#include <iostream>
#include <vector>

#include "day_08.h"

#include <map>

using namespace std;

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

            // check left to right
            u_int64_t looking_left_scenic_score = 0;
            for (auto it = forest_row.rbegin() + 1; it != forest_row.rend(); ++it, looking_left_scenic_score++) {
                if (*it >= tree_size) break;
            }

            // check top to bottom
            u_int64_t looking_down_scenic_score = 0;
            for (size_t cursor_row = row + 1; cursor_row < column_size; cursor_row++) {
                const auto view_tree_size = forest[cursor_row][column];
                looking_down_scenic_score++;
                if (view_tree_size >= tree_size) break;
            }

            // check bottom_to_top
            u_int64_t looking_top_scenic_score = 0;
            for (long cursor_row = row_long - 1; cursor_row >= 0; cursor_row--) {
                const auto view_tree_size = forest[cursor_row][column];
                looking_top_scenic_score++;
                if (view_tree_size >= tree_size) break;
            }

            u_int64_t scenic_score = looking_right_scenic_score * looking_left_scenic_score *
                                     looking_down_scenic_score * looking_top_scenic_score;

            cout << "Scenic score for tree at (" << row << ", " << column << "): " << scenic_score << endl;

            if (scenic_score > max_scenic_score) max_scenic_score = scenic_score;
        }
    }

    cout << endl;
    cout << "Max scenic score: " << max_scenic_score << endl;
}
