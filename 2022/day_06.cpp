//
// Created by Theotime Poisseau on 08/10/2025.
// https://adventofcode.com/2022/day/6
//

#include <string>
#include <fstream>
#include <iostream>
#include <set>
#include <map>

using namespace std;

void day_06_part_1() {
    ifstream input(filesystem::current_path().append("2022/inputs/day_06.txt"));
    if (!input.is_open()) throw runtime_error("Unable to open file");

    string line;
    getline(input, line);

    cout << line << endl;

    set<char> seen{};
    auto index = 0;
    for (; index <= line.size(); index++) {
        const char c = line[index];
        if (seen.contains(c)) {
            seen.clear();
            seen.insert(c);
            continue;
        }

        seen.insert(c);

        if (seen.size() == 4) {
            break;
        }
    }

    const auto start_of_packet_character_count = index + 1;
    cout << "start-of-packet marker end: " << start_of_packet_character_count << endl;
}

void day_06_part_2() {
    ifstream input(filesystem::current_path().append("2022/inputs/day_06.txt"));
    if (!input.is_open()) throw runtime_error("Unable to open file");

    string line;
    getline(input, line);

    cout << line << endl;

    map<char, size_t> seen{};
    size_t index = 0;
    for (; index < line.size(); index++) {
        const char c = line[index];
        if (seen.contains(c)) {
            const auto occurence_index = seen[c];
            index = occurence_index;
            seen.clear();
            continue;
        }

        seen.emplace(c, index);
        if (seen.size() == 14) {
            break;
        }
    }

    const auto start_of_message_character_count = index + 1;
    cout << "start-of-packet marker end: " << start_of_message_character_count << endl;
}
