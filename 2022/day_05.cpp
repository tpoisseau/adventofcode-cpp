//
// Created by Theotime Poisseau on 08/10/2025.
// https://adventofcode.com/2022/day/5
//

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

#include <list>
#include <map>

#include <ranges>

// #include "day_05.h"

using namespace std;

constexpr char DELIMITER = ' ';

void parse_movement_instruction(string &instruction, u_int &quantity, u_int &from, u_int &to) {
    stringstream ss(instruction);
    string quantity_str, from_str, to_str, void_str;

    // move 1 from 2 to 1
    getline(ss, void_str, DELIMITER); // 1 from 2 to 1
    getline(ss, quantity_str, DELIMITER); // from 2 to 1
    getline(ss, void_str, DELIMITER); // 2 to 1
    getline(ss, from_str, DELIMITER); // to 1
    getline(ss, void_str, DELIMITER); // 1
    getline(ss, to_str);

    quantity = static_cast<u_int>(stoi(quantity_str));
    from = static_cast<u_int>(stoi(from_str));
    to = static_cast<u_int>(stoi(to_str));
}

void day_05_part_1() {
    ifstream input(filesystem::current_path().append("2022/inputs/day_05.txt"));
    if (!input.is_open()) throw runtime_error("Unable to open file");

    map<u_int, list<char> > stacks{};
    string line;
    while (getline(input, line)) {
        if (line.empty()) break; // break on the empty line to read the second part of the data

        for (u_int str_index = 1, stack_key = 1; str_index < line.size(); str_index += 4, stack_key++) {
            const char crate = line[str_index];
            if (crate == ' ') continue; // ignore empty spaces
            if (crate >= '1' && crate <= '9') break; // ignore explicit stacks assignment

            stacks[stack_key].push_front(crate);
        }
    }

    cout << "Initial stacks:" << endl << format("{}", stacks) << endl;

    while (getline(input, line)) {
        u_int quantity, from, to;
        parse_movement_instruction(line, quantity, from, to);

        auto &stack_from = stacks[from];
        auto &stack_to = stacks[to];
        for (u_int i = 0; i < quantity; i++) {
            const char crate = stack_from.back();
            stack_from.pop_back();
            stack_to.push_back(crate);
        }

        cout << line << " | " << format("{}", stacks) << endl;
    }

    stringstream ss;
    for (const auto &stack: stacks | views::values) {
        ss << stack.back();
    }
    cout << "Final stacks word:" << endl << ss.str() << endl;
}

void day_05_part_2() {
    ifstream input(filesystem::current_path().append("2022/inputs/day_05.txt"));
    if (!input.is_open()) throw runtime_error("Unable to open file");

    map<u_int, list<char> > stacks{};
    string line;
    while (getline(input, line)) {
        if (line.empty()) break; // break on the empty line to read the second part of the data

        for (u_int str_index = 1, stack_key = 1; str_index < line.size(); str_index += 4, stack_key++) {
            const char crate = line[str_index];
            if (crate == ' ') continue; // ignore empty spaces
            if (crate >= '1' && crate <= '9') break; // ignore explicit stacks assignment

            stacks[stack_key].push_front(crate);
        }
    }

    cout << "Initial stacks:" << endl << format("{}", stacks) << endl;

    while (getline(input, line)) {
        u_int quantity, from, to;
        parse_movement_instruction(line, quantity, from, to);

        auto &stack_from = stacks[from];
        list<char> temp_stack;
        for (u_int i = 0; i < quantity; i++) {
            const char crate = stack_from.back();
            stack_from.pop_back();
            temp_stack.push_front(crate);
        }

        auto &stack_to = stacks[to];
        stack_to.insert(stack_to.end(), temp_stack.begin(), temp_stack.end());

        cout << line << " | " << format("{}", stacks) << endl;
    }

    stringstream ss;
    for (const auto &stack: stacks | views::values) {
        ss << stack.back();
    }
    cout << "Final stacks word:" << endl << ss.str() << endl;
}
