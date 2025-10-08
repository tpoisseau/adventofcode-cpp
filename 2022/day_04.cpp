//
// Created by Theotime Poisseau on 08/10/2025.
// https://adventofcode.com/2022/day/4
//

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

#include "day_04.h"

using namespace std;

constexpr char DELIMITER_PAIR = ',';
constexpr char DELIMITER_RANGE = '-';

/**
 * A procedure to assign first_min, first_max, second_min, second_max from line parsing
 *
 * @param line the line to parse, pass by reference to avoid unnecessary copy
 * @param first_min
 * @param first_max
 * @param second_min
 * @param second_max
 */
void parse_line(string &line, int &first_min, int &first_max, int &second_min, int &second_max) {
    stringstream ss(line);
    string first_min_str, first_max_str;
    string second_min_str, second_max_str;

    getline(ss, first_min_str, DELIMITER_RANGE);
    getline(ss, first_max_str, DELIMITER_PAIR);
    getline(ss, second_min_str, DELIMITER_RANGE);
    getline(ss, second_max_str);
    cout << first_min_str << "-" << first_max_str << "," << second_min_str << "-" << second_max_str << endl;

    first_min = stoi(first_min_str);
    first_max = stoi(first_max_str);
    second_min = stoi(second_min_str);
    second_max = stoi(second_max_str);
}

void day_04_part_1() {
    ifstream input(filesystem::current_path().append("2022/inputs/day_04.txt"));
    if (!input.is_open()) throw runtime_error("Unable to open file");

    string line;
    u_int overlaps = 0;
    while (getline(input, line)) {
        if (line.empty()) continue;

        int first_min, first_max, second_min, second_max;
        parse_line(line, first_min, first_max, second_min, second_max);

        const bool first_contains_second = first_min <= second_min && second_max <= first_max;
        const bool second_contains_first = second_min <= first_min && first_max <= second_max;
        if (first_contains_second || second_contains_first) overlaps++;

        if (first_contains_second) cout << "First contains second" << endl;
        else if (second_contains_first) cout << "Second contains first" << endl;
    }

    cout << "Overlaps: " << overlaps << endl;
}

void day_04_part_2() {
    ifstream input(filesystem::current_path().append("2022/inputs/day_04.txt"));
    if (!input.is_open()) throw runtime_error("Unable to open file");

    string line;
    u_int overlaps = 0;
    while (getline(input, line)) {
        if (line.empty()) continue;

        int first_min, first_max, second_min, second_max;
        parse_line(line, first_min, first_max, second_min, second_max);

        const bool is_left_overlap = first_min <= second_min && second_min <= first_max;
        const bool is_right_overlap = second_min <= first_min && first_min <= second_max;
        if (is_left_overlap || is_right_overlap) overlaps++;

        if (is_left_overlap) cout << "Left overlap" << endl;
        else if (is_right_overlap) cout << "Right overlap" << endl;
    }

    cout << "Overlaps: " << overlaps << endl;
}
