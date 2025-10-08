//
// Created by Theotime Poisseau on 08/10/2025.
//

#include <string>
#include <fstream>
#include <iostream>
#include <set>
#include <vector>
#include <algorithm>

#include "day_03.h"

using namespace std;

u_int get_priority(const char value) {
    if (value >= 'a' && value <= 'z') return value - 'a' + 1;
    if (value >= 'A' && value <= 'Z') return value - 'A' + 1 + 26;
    throw invalid_argument("char should be a letter in A-Z or a-z range");
}

void day_03_part_1() {
    ifstream input(filesystem::current_path().append("2022/inputs/day_03.txt"));
    if (!input.is_open()) throw runtime_error("Unable to open file");

    string line;
    u_int total_priority = 0;
    while (getline(input, line)) {
        if (line.empty()) continue;

        u_long middle = line.size() / 2;
        string first_str(line.begin(), line.begin() + middle);
        string second_str(line.end() - middle, line.end());
        cout << first_str << " # " << second_str << endl;

        set<char> first{};
        set<char> second{};
        first.insert(line.begin(), line.begin() + middle);
        second.insert(line.end() - middle, line.end());

        vector<char> intersection{};
        ranges::set_intersection(first, second, back_inserter(intersection));
        if (intersection.size() != 1) throw out_of_range("It should have exactly one char in the intersection");

        string intersection_str(intersection.begin(), intersection.end());
        auto priority = get_priority(intersection_str[0]);
        cout << "Intersection char: " << intersection_str << ", Priority: " << priority << endl;

        total_priority += priority;
    }

    cout << endl << "Total priority: " << total_priority << endl;
}

void day_03_part_2() {
    ifstream input(filesystem::current_path().append("2022/inputs/day_03.txt"));
    if (!input.is_open()) throw runtime_error("Unable to open file");

    string line;
    u_int total_priority = 0;
    vector<string> chunk{};
    while (getline(input, line)) {
        if (line.empty()) continue;

        chunk.push_back(line);
        if (chunk.size() != 3) continue;

        string first_str = chunk[0];
        set<char> first(first_str.begin(), first_str.end());
        string second_str = chunk[1];
        set<char> second(second_str.begin(), second_str.end());
        string third_str = chunk[2];
        set<char> third(third_str.begin(), third_str.end());

        vector<char> intersection_first_second{};
        vector<char> intersection{};
        ranges::set_intersection(first, second, back_inserter(intersection_first_second));
        ranges::set_intersection(third, intersection_first_second, back_inserter(intersection));
        if (intersection.size() != 1) throw out_of_range("It should have exactly one char in the intersection");

        auto priority = get_priority(intersection[0]);
        string intersection_str(intersection.begin(), intersection.end());
        cout << first_str << " # " << second_str << " # " << third_str << endl;
        cout << "Intersection char: " << intersection_str << ", Priority: " << priority << endl;

        total_priority += priority;
        chunk.clear();
    }

    cout << endl << "Total priority: " << total_priority << endl;
}
