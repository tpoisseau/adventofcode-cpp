//
// Created by Theotime Poisseau on 03/12/2025.
//

#include "day_03.h"

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <ranges>

using namespace std;

u_short char_to_unsigned_short(const char c) {
    return static_cast<u_short>(c - '0');
}

void day_03_part_1_2025() {
    ifstream input(filesystem::current_path().append("2025/inputs/day_03.txt"));
    if (!input.is_open()) throw runtime_error("Unable to open file");

    string line;

    uint64_t total_jolts = 0;
    while (getline(input, line)) {
        if (line.empty()) break;

        auto range_init = line | views::transform(char_to_unsigned_short);
        auto bank = vector(range_init.begin(), range_init.end());

        u_short max_jolts = 0;
        for (size_t i = 0; i < bank.size(); i++) {
            const auto battery_left = bank[i];

            for (size_t j = i + 1; j < bank.size(); j++) {
                const auto battery_right = bank[j];
                const u_short jolts = battery_left * 10 + battery_right;

                if (jolts > max_jolts) max_jolts = jolts;
            }
        }

        cout << line << " max_jolts: " << max_jolts << endl;
        total_jolts += max_jolts;
    }

    cout << "Total jolts: " << total_jolts << endl;
}

uint64_t get_max_jolt(
    const vector<u_short> &bank,
    const size_t index,
    const u_short jolt_to_take,
    const uint64_t current_jolt
) {
    if (jolt_to_take == 0) return current_jolt;

    if ((index + jolt_to_take) > bank.size()) return 0;

    u_int64_t max_jolts = bank[index];
    size_t max_index = index;

    for (size_t i = index; i < bank.size(); i++) {
        if (i + jolt_to_take > bank.size()) break;

        const auto jolt = bank[i];
        if (jolt <= max_jolts) continue;
        max_jolts = jolt;
        max_index = i;
    }

    return get_max_jolt(bank, max_index + 1, jolt_to_take - 1, current_jolt * 10ull + max_jolts);
}

void day_03_part_2_2025() {
    ifstream input(filesystem::current_path().append("2025/inputs/day_03.txt"));
    if (!input.is_open()) throw runtime_error("Unable to open file");

    string line;

    uint64_t total_jolts = 0;
    while (getline(input, line)) {
        if (line.empty()) break;

        auto range_init = line | views::transform(char_to_unsigned_short);
        auto bank = vector(range_init.begin(), range_init.end());

        const uint64_t max_jolts = get_max_jolt(bank, 0, 12, 0);
        cout << line << " max_jolts: " << max_jolts << endl;
        total_jolts += max_jolts;
    }

    cout << "Total jolts: " << total_jolts << endl;
}
