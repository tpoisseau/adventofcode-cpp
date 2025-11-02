//
// Created by Theotime Poisseau on 01/11/2025.
// https://adventofcode.com/2022/day/9#part2
//

#include "day_09.h"

#include <string>
#include <fstream>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

struct Point {
    int64_t x;
    int64_t y;

    // comparator for set
    bool operator <(const Point &point) const {
        return x < point.x || (x == point.x && y < point.y);
    }
};

std::ostream &operator<<(std::ostream &os, Point const &arg) {
    os << "Point{.x=" << arg.x << ", .y= " << arg.y << "}";
    return os;
}

enum Direction {
    UP = 'U',
    DOWN = 'D',
    LEFT = 'L',
    RIGHT = 'R'
};

struct Command {
    Direction direction;
    uint64_t distance;
};

std::ostream &operator<<(std::ostream &os, Command const &arg) {
    os << "Command{.direction=" << string(1, arg.direction) << ", .distance=" << arg.distance << "}";
    return os;
}

Command parse_command(const string &command) {
    const auto direction = static_cast<Direction>(command[0]);
    const uint64_t distance = stoull(command.substr(2));

    return {direction, distance};
}

void execute_command(
    const Command command,
    Point &head, Point &tail,
    set<Point> &tail_positions, vector<Point> &tail_positions_debug
) {
    int64_t move_x = 0;
    int64_t move_y = 0;
    switch (command.direction) {
        case UP:
            move_y = 1;
            break;
        case DOWN:
            move_y = -1;
            break;
        case LEFT:
            move_x = -1;
            break;
        case RIGHT:
            move_x = 1;
            break;
    }
    auto apply_head_move = [&] {
        head.x += move_x;
        head.y += move_y;
    };

    for (uint64_t i = 0; i < command.distance; i++) {
        const int64_t hx = head.x;
        const int64_t hy = head.y;
        apply_head_move();

        const int64_t dx = head.x - tail.x;
        const int64_t dy = head.y - tail.y;
        const int64_t dx_abs = abs(dx);
        const int64_t dy_abs = abs(dy);
        if (dx_abs > 1 || dy_abs > 1) {
            tail.x = hx;
            tail.y = hy;
        }

        if (!tail_positions.contains(tail)) {
            tail_positions.emplace(tail);
            tail_positions_debug.emplace_back(tail);
        }
    }
}

void day_09_part_1() {
    ifstream input(filesystem::current_path().append("2022/inputs/day_09.txt"));
    if (!input.is_open()) throw runtime_error("Unable to open file");

    string line;

    Point head{};
    Point tail{};
    vector tail_positions_debug{tail};
    set tail_positions{tail};
    while (getline(input, line)) {
        auto command = parse_command(line);
        cout << command << endl;
        execute_command(command, head, tail, tail_positions, tail_positions_debug);
        cout << "Head: " << head << endl;
        cout << "Tail: " << tail << endl;
        cout << endl;
    }

    for (auto point: tail_positions_debug) {
        cout << point << endl;
    }
    cout << "Total tail positions: " << tail_positions.size() << endl;
}

void day_09_part_2() {
}
