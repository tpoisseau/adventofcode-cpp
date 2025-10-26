//
// Created by Theotime Poisseau on 22/10/2025.
//

#ifndef ADVENT_OF_CODE_CPP_ITERATORS_H
#define ADVENT_OF_CODE_CPP_ITERATORS_H
#include <cstddef>

#include <iostream>
#include <ranges>

/**
 * `mdspan` https://en.cppreference.com/w/cpp/container/mdspan.html
 * permit to view containers like vector as an N dimensions matrix.
 * But it does not expose any iterator.
 *
 * `std::views::iota` can be used as a basic index iterator; unfortunately, there is no reverse version of iota.
 */
namespace aoc::iterators {
    using namespace std;

    /**
     * iota_reverse(5): 5 4 3 2 1 0
     * iota_reverse(5, 1): 4 3 2 1 0
     * iota_reverse(0): 0
     * iota_reverse(0, 1, 0):
     * iota_reverse(1): 1 0
     * iota_reverse(1, 1, 0): 0
     *
     * @param start
     * @param minus_start
     * @param end
     * @return a view of a size_t sequence
     */
    inline auto iota_reverse(const size_t start, const size_t minus_start = 0, const size_t end = 0) {
        size_t iota_start;
        size_t iota_end;

        if (minus_start > start) {
            iota_start = 0;
            iota_end = 0;
        } else {
            iota_start = start - minus_start;
            if (end > iota_start) {
                iota_start = 0;
                iota_end = 0;
            } else {
                iota_end = 1 + iota_start + iota_start - end;
            }
        }

        auto cursor = iota_start;
        return views::iota(iota_start, iota_end)
               | views::transform([cursor](auto _v) mutable { return cursor--; });
    }

    void print_iterable(auto it) {
        for (auto value: it) {
            cout << value << " ";
        }
        cout << endl;
    }

    auto count(auto &it, auto init) {
        auto count = init;

        for (auto value: it) {
            ++count;
        }

        return count;
    }

    /**
     * @param matrix mdspan
     * @param current_row the row where the iteration is scoped
     * @param initial_column the starting column, it should be 0
     * @return an iterator / view of tuple(column, matrix[current_row, column])
     */
    auto matrix_horizontal_it(const auto &matrix, const size_t current_row, const size_t initial_column) {
        const auto column_size = matrix.extent(1);

        return views::iota(initial_column, column_size)
               | views::transform([&matrix, current_row](auto const column_view) {
                   return tuple<size_t, size_t>{column_view, matrix[current_row, column_view]};
               });
    }

    /**
     * @param matrix mdspan
     * @param current_row the row where the iteration is scoped
     * @param initial_column the starting column
     * @param minus_initial_column the offset to decrement (unsigned requires extra steps to apply safe offset)
     * @return an iterator / view of tuple(column, matrix[current_row, column]) from initial_column - minus_initial_column to 0
     */
    auto matrix_horizontal_reverse_it(
        const auto &matrix,
        const size_t current_row,
        const size_t initial_column,
        const size_t minus_initial_column
    ) {
        return iota_reverse(initial_column, minus_initial_column)
               | views::transform([&matrix, current_row](const auto column_view) {
                   return tuple<size_t, size_t>{column_view, matrix[current_row, column_view]};
               });
    }

    /**
     * @param matrix mdspan
     * @param current_column the column where the iteration is scoped
     * @param initial_row the starting row, it should be 0
     * @return an iterator / view of tuple(row, matrix[current_row, row])
     */
    auto matrix_vertical_it(const auto &matrix, const size_t current_column, const size_t initial_row) {
        const auto row_size = matrix.extent(0);

        return views::iota(initial_row, row_size)
               | views::transform([&matrix, current_column](const auto row_view) {
                   return tuple<size_t, size_t>{row_view, matrix[row_view, current_column]};
               });
    }

    /**
     * @param matrix mdspan
     * @param current_column the column where the iteration is scoped
     * @param initial_row the starting row
     * @param minus_initial_row the offset to decrement (unsigned requires extra steps to apply safe offset)
     * @return an iterator / view of tuple(row, matrix[current_row, row])
     */
    auto matrix_vertical_reverse_it(
        const auto &matrix,
        const size_t current_column,
        const size_t initial_row,
        const size_t minus_initial_row
    ) {
        return iota_reverse(initial_row, minus_initial_row)
               | views::transform([&matrix, current_column](const auto row_view) {
                   return tuple<size_t, size_t>{row_view, matrix[row_view, current_column]};
               });
    }
}


#endif //ADVENT_OF_CODE_CPP_ITERATORS_H
