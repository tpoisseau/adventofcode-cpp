//
// Created by Theotime Poisseau on 07/10/2025.
// https://adventofcode.com/2022/day/1
//

#include <string>
#include <fstream>
#include <iostream>
#include <list>

#include "day_01.h"

void day_01_part_1() {
    std::string line;
    std::ifstream input(std::filesystem::current_path().append("2022/inputs/day_01.txt"));

    if (!input.is_open()) {
        std::cout << "Unable to open file";
        return;
    }

    u_int max = 0;
    u_int current = 0;
    u_int elf_index = 0;
    u_int elf_max = 0;

    while (getline(input, line)) {
        if (line.empty()) {
            if (current > max) {
                max = current;
                elf_max = elf_index;
            }
            current = 0;
            elf_index++;
            continue;
        }
        current += std::stoi(line);
    }

    std::cout << "Max: " << max << ", with Elf index: " << elf_max << std::endl;
}

void day_01_part_2() {
    std::string line;
    std::ifstream input(std::filesystem::current_path().append("2022/inputs/day_01.txt"));

    if (!input.is_open()) {
        std::cout << "Unable to open file";
        return;
    }

    auto elves = std::list<u_int>();
    u_int current = 0;

    while (getline(input, line)) {
        if (line.empty()) {
            elves.push_back(current);
            current = 0;
            continue;
        }

        current += std::stoi(line);
    }

    elves.sort(std::greater<>());

    u_int top_three = elves.front();
    elves.pop_front();
    top_three += elves.front();
    elves.pop_front();
    top_three += elves.front();

    std::cout << top_three << std::endl;
}
