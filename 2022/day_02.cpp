//
// Created by Theotime Poisseau on 08/10/2025.
// https://adventofcode.com/2022/day/2
//

#include "day_02.h"

#include <string>
#include <fstream>
#include <iostream>

using namespace std;

constexpr char ROCK = 'A';
constexpr char ROCK_ENCRYPTED = 'X';
constexpr char PAPER = 'B';
constexpr char PAPER_ENCRYPTED = 'Y';
constexpr char SCISSORS = 'C';
constexpr char SCISSORS_ENCRYPTED = 'Z';

u_int get_shape_score(const char shape) {
    return static_cast<u_int>(shape - ('A' - 1));
}

char decrypt_shape(const char shape) {
    return static_cast<char>(shape - ('X' - 'A'));
}

u_int get_outcome_score(const char opponent, const char move) {
    switch (opponent) {
        case ROCK:
            switch (move) {
                case ROCK:
                    return 3;
                case PAPER:
                    return 6;
                case SCISSORS:
                    return 0;
                default:
                    throw std::out_of_range("Invalid move");
            }
        case PAPER:
            switch (move) {
                case ROCK:
                    return 0;
                case PAPER:
                    return 3;
                case SCISSORS:
                    return 6;
                default:
                    throw std::out_of_range("Invalid move");
            }
        case SCISSORS:
            switch (move) {
                case ROCK:
                    return 6;
                case PAPER:
                    return 0;
                case SCISSORS:
                    return 3;
                default:
                    throw std::out_of_range("Invalid move");
            }
        default:
            throw std::out_of_range("Invalid opponent");
    }
}

void day_02_part_1() {
    string line;
    std::ifstream input(std::filesystem::current_path().append("2022/inputs/day_02.txt"));

    if (!input.is_open()) {
        cout << "Unable to open file";
        return;
    }

    u_int total_score = 0;
    while (getline(input, line)) {
        const char opponent = line[0];
        const char move_encrypted = line[2];
        const char move = decrypt_shape(move_encrypted);
        const u_int outcome_score = get_outcome_score(opponent, move);
        const u_int shape_score = get_shape_score(move);
        const u_int score = outcome_score + shape_score;

        cout << "Opponent: " << opponent << ", Move: " << move << ", Outcome: " << outcome_score << ", Shape: " <<
                shape_score << ", Score: " << score << endl;

        total_score += score;
    }

    cout << endl << "Total Score: " << total_score << endl;
}

constexpr char LOSE = 'X';
constexpr char DRAW = 'Y';
constexpr char WIN = 'Z';

char get_move(const char opponent, const char target_outcome) {
    switch (opponent) {
        case ROCK:
            switch (target_outcome) {
                case LOSE:
                    return SCISSORS;
                case DRAW:
                    return ROCK;
                case WIN:
                    return PAPER;
                default:
                    throw std::out_of_range("Invalid target outcome");
            }
        case PAPER:
            switch (target_outcome) {
                case LOSE:
                    return ROCK;
                case DRAW:
                    return PAPER;
                case WIN:
                    return SCISSORS;
                default:
                    throw std::out_of_range("Invalid target outcome");
            }
        case SCISSORS:
            switch (target_outcome) {
                case LOSE:
                    return PAPER;
                case DRAW:
                    return SCISSORS;
                case WIN:
                    return ROCK;
                default:
                    throw std::out_of_range("Invalid target outcome");
            }
        default:
            throw std::out_of_range("Invalid opponent");
    }
}

void day_02_part_2() {
    string line;
    std::ifstream input(std::filesystem::current_path().append("2022/inputs/day_02.txt"));

    if (!input.is_open()) {
        cout << "Unable to open file";
        return;
    }

    u_int total_score = 0;
    while (getline(input, line)) {
        const char opponent = line[0];
        const char target_outcome = line[2];
        const char move = get_move(opponent, target_outcome);
        const u_int outcome_score = get_outcome_score(opponent, move);
        const u_int shape_score = get_shape_score(move);
        const u_int score = outcome_score + shape_score;

        cout << "Opponent: " << opponent << ", Move: " << move << ", Outcome: " << outcome_score << ", Shape: " <<
                shape_score << ", Score: " << score << endl;

        total_score += score;
    }

    cout << endl << "Total Score: " << total_score << endl;
}