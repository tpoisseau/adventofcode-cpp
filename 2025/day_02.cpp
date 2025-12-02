//
// Created by Theotime Poisseau on 02/12/2025.
//

#include "day_02.h"

#include <string>
#include <fstream>
#include <iostream>

using namespace std;


void day_02_part_1_2025() {
    ifstream input(filesystem::current_path().append("2025/inputs/day_02.txt"));
    if (!input.is_open()) throw runtime_error("Unable to open file");

    unsigned long long sum_invalid_ids = 0;
    while (true) {
        string s_start;
        string s_end;

        getline(input, s_start, '-');
        getline(input, s_end, ',');

        if (s_start.empty()) break;

        auto start = stoull(s_start);
        auto end = stoull(s_end);

        cout << format("Invalid IDs in range {} - {}: ", start, end);
        for (unsigned long long i = start; i <= end; i++) {
            auto s = to_string(i);
            auto s_length = s.length();
            if (s_length % 2 == 1) continue;

            auto middle = s_length / 2;
            auto first_half = s.substr(0, middle);
            auto second_half = s.substr(middle);
            if (first_half != second_half) continue;

            sum_invalid_ids += i;
            cout << format(", {}", i);
        }
        cout << endl;
    }

    cout << "Sum of invalid IDs: " << sum_invalid_ids << endl;
}

void day_02_part_2_2025() {
}
