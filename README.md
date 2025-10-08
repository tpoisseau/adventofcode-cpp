# Advent of Code - CPP

This repo stores my solutions for the Advent of Code challenges in C++.

## Structure of the repo

```
advent-of-code-cpp/
├── 20XX                            # Year folder.
│   ├── day_xx.cpp                  # One source file per day.
│   ├── day_xx.h                    # with his header file.
│   └── inputs
│       ├── day_xx.txt              # Input dataset. ignored by git. AoC ask to not publish dataset.
│       ├── day_xx_ex.txt           # Input dataset example.
├── CMakeLists.txt                  # Automatically updated by my IDE (CLion from jetbrains)
├── README.md                       # This file.
└── main.cpp                        # Entry point of the program.
```

Each header day file declares two functions:

```cpp
void day_XX_part_1();

void day_XX_part_2();
```

replace XX with the day number.

## Requirements

- Build chain C++26+
- CMake 4+

## How to use

1. Put the input dataset has `20XX/inputs/day_XX.txt`.
2. Ensure corresponding `day_XX.cpp` use the right input file (and not the `_ex.txt` file).
3. Edit `main.cpp` to `#include` the right day header file.
4. Edit `main.cpp` to call the right day function `day_XX_part_1()` or `day_XX_part_2()`.
5. Build and run.

## Build & Run

```
# Build
cmake --build cmake-build-debug --target advent_of_code_cpp -j 8

# Run
./cmake-build-debug/advent_of_code_cpp
```

Or add a CMake Application run configuration in your IDE,
with the current working directory set to the root of the repo.
