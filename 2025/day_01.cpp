//
// Created by Theotime Poisseau on 01/12/2025.
//

#include "day_01.h"
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

enum Direction {
    LEFT = 'L',
    RIGHT = 'R'
};

struct Command {
    Direction direction;
    int distance;
};

Command parse_command(const string &command) {
    const auto direction = static_cast<Direction>(command[0]);
    const int distance = stoi(command.substr(1));

    return {direction, distance};
}

void execute_command(const Command &command, int &cursor) {
    if (command.direction == LEFT) {
        cursor = (cursor + (100 - command.distance)) % 100;
    } else cursor = (cursor + command.distance) % 100;
}

void execute_command(const Command &command, int &cursor, int &password) {
    int temp = cursor;
    if (command.direction == LEFT) {
        for (int i = 0; i < command.distance; i++) {
            temp -= 1;
            if (temp == 0) password++;
            if (temp < 0) temp = 99;
        }
    } else {
        for (int i = 0; i < command.distance; i++) {
            temp += 1;
            if (temp > 99) temp = 0;
            if (temp == 0) password++;
        }
    }

    cursor = temp;
}

void day_01_part_1_2025() {
    ifstream input(filesystem::current_path().append("2025/inputs/day_01.txt"));
    if (!input.is_open()) throw runtime_error("Unable to open file");

    string line;

    int cursor = 50;
    int password = 0;
    while (getline(input, line)) {
        if (line.empty()) break;

        const auto command = parse_command(line);
        execute_command(command, cursor);

        cout << "Command " << static_cast<char>(command.direction) << "" << command.distance << " -> " << cursor <<
                endl;
        if (cursor == 0) password++;
    }

    cout << "Password: " << password << endl;
}

void day_01_part_2_2025() {
    ifstream input(filesystem::current_path().append("2025/inputs/day_01.txt"));
    if (!input.is_open()) throw runtime_error("Unable to open file");

    string line;

    int cursor = 50;
    int password = 0;
    while (getline(input, line)) {
        if (line.empty()) break;

        const auto command = parse_command(line);
        execute_command(command, cursor, password);

        cout << "Command " << static_cast<char>(command.direction) << "" << command.distance << " -> " << cursor <<
                endl;
    }

    cout << "Password: " << password << endl;
}
