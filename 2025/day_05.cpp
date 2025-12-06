//
// Created by Theotime Poisseau on 05/12/2025.
//

#include "day_05.h"

#include <string>
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <sstream>

using namespace std;

constexpr char DELIMITER_RANGE = '-';

pair<uint64_t, uint64_t> get_range(const string &line) {
    stringstream ss(line);
    string start_str, end_str;

    getline(ss, start_str, DELIMITER_RANGE);
    getline(ss, end_str);

    uint64_t start = stoull(start_str);
    uint64_t end = stoull(end_str);

    return {start, end};
}

void day_05_part_1_2025() {
    list<pair<uint64_t, uint64_t> > fresh_ingredients;
    ifstream input(filesystem::current_path().append("2025/inputs/day_05.txt"));
    if (!input.is_open()) throw runtime_error("Unable to open file");

    string line;
    while (getline(input, line)) {
        if (line.empty()) break;

        cout << line << endl;
        auto range = get_range(line);
        fresh_ingredients.push_back(range);
    }
    fresh_ingredients.sort();
    cout << endl;

    uint64_t available_ingredients = 0;
    while (getline(input, line)) {
        if (line.empty()) break;

        const auto id = stoull(line);
        cout << id << " ";
        for (const auto entry: fresh_ingredients) {
            const auto [start, end] = entry;
            if (id < start || id > end) continue;

            available_ingredients++;
            cout << format("Fresh, in range {}-{}", start, end);
            break;
        }
        cout << endl;
    }

    cout << "Available ingredients: " << available_ingredients << endl;
}

void day_05_part_2_2025() {
    multimap<uint64_t, uint64_t> raw_fresh_ingredients;
    ifstream input(filesystem::current_path().append("2025/inputs/day_05.txt"));
    if (!input.is_open()) throw runtime_error("Unable to open file");

    string line;
    while (getline(input, line)) {
        if (line.empty()) break;

        cout << line << endl;
        raw_fresh_ingredients.emplace(get_range(line));
    }
    cout << endl;

    map<uint64_t, uint64_t> fresh_ingredients;
    for (
        auto it = raw_fresh_ingredients.begin();
        it != raw_fresh_ingredients.end();
        it = raw_fresh_ingredients.upper_bound(it->first)
    ) {
        uint64_t start = it->first;
        uint64_t end = it->second;

        // set the highest end possible
        auto range = raw_fresh_ingredients.equal_range(start);
        for (auto it_range = range.first; it_range != range.second; ++it_range) {
            const auto possible_end = it_range->second;
            if (end > possible_end) continue;
            end = possible_end;
        }

        // translate start to the highest end possible from ordered existing ranges
        for (auto [ordered_start, ordered_end]: fresh_ingredients) {
            if (start >= ordered_start && start <= ordered_end) start = ordered_end + 1;
            if (end < start) break;
        }

        // continue if translations gone too far
        if (end < start) continue;

        // add sanitized range
        fresh_ingredients.emplace(start, end);
    }

    uint64_t fresh_ingredients_count = 0;
    for (auto [start, end]: fresh_ingredients) {
        cout << format("Range {}-{}", start, end) << endl;
        fresh_ingredients_count += end - start + 1;
    }

    cout << "Total Fresh Ingredients: " << fresh_ingredients_count << endl;
}
