//
// Created by Theotime Poisseau on 09/10/2025.
// https://adventofcode.com/2022/day/7
//

#include <string>
#include <fstream>
#include <iostream>
#include <ranges>
#include <sstream>
#include <unordered_map>
#include <list>

using namespace std;

struct Node {
    string name;
    u_int64_t value{};
    unordered_map<string, Node> children;
    Node *parent = nullptr;
};

void print_tree(Node &node, u_int indent = 0) {
    for (u_int i = 0; i < indent; i++) cout << "\t";

    if (node.value == 0) {
        cout << format("- {} (dir)", node.name);
    } else {
        cout << format("- {} (file, size={})", node.name, node.value);
    }
    cout << endl;

    for (auto &val: node.children | views::values) {
        print_tree(val, indent + 1);
    }
}

u_int64_t walk_sum_tree(Node &node, unordered_map<Node *, u_int64_t> &flat_folder_sizes) {
    u_int64_t sum = node.value;

    for (auto &val: node.children | views::values) {
        sum += walk_sum_tree(val, flat_folder_sizes);
    }

    if (node.value == 0) {
        flat_folder_sizes.emplace(&node, sum);
    }

    return sum;
}

void day_07_part_1() {
    ifstream input(filesystem::current_path().append("2022/inputs/day_07.txt"));
    if (!input.is_open()) throw runtime_error("Unable to open file");

    string line;
    getline(input, line); // skip the first line

    Node root = {.name = "/"};
    Node *current = &root;

    while (getline(input, line)) {
        stringstream ss(line);
        string first_part;
        getline(ss, first_part, ' ');

        if (first_part == "$") {
            // command
            string command;
            getline(ss, command, ' ');

            if (command == "ls") continue;
            if (command == "cd") {
                string dir;
                getline(ss, dir);

                current = dir == ".." ? current->parent : &current->children[dir];
            }
        } else if (first_part == "dir") {
            string dir;
            getline(ss, dir);
            current->children[dir] = Node{.name = dir, .parent = current};
        } else {
            const auto &size_str = first_part;
            string name;
            getline(ss, name);

            auto value_signed = stoll(size_str);
            current->children[name] = Node{
                .name = name,
                .value = static_cast<make_unsigned_t<long long>>(value_signed),
                .parent = current,
            };
        }
    }

    print_tree(root);

    cout << "\n---\n" << endl;

    unordered_map<Node *, u_int64_t> flat_folder_sizes;
    walk_sum_tree(root, flat_folder_sizes);

    u_int64_t total_size_of_small_folders = 0;
    for (auto &val: flat_folder_sizes) {
        u_int64_t size = val.second;

        cout << format("{}: {}", val.first->name, size) << endl;

        if (size >= 100000) continue;
        total_size_of_small_folders += size;
    }

    cout << "\n---\n" << endl;

    cout << "Total size of small folders: " << total_size_of_small_folders << endl;
}

void day_07_part_2() {
    ifstream input(filesystem::current_path().append("2022/inputs/day_07.txt"));
    if (!input.is_open()) throw runtime_error("Unable to open file");

    string line;
    getline(input, line); // skip the first line

    Node root = {.name = "/"};
    Node *current = &root;

    while (getline(input, line)) {
        stringstream ss(line);
        string first_part;
        getline(ss, first_part, ' ');

        if (first_part == "$") {
            // command
            string command;
            getline(ss, command, ' ');

            if (command == "ls") continue;
            if (command == "cd") {
                string dir;
                getline(ss, dir);

                current = dir == ".." ? current->parent : &current->children[dir];
            }
        } else if (first_part == "dir") {
            string dir;
            getline(ss, dir);
            current->children[dir] = Node{.name = dir, .parent = current};
        } else {
            const auto &size_str = first_part;
            string name;
            getline(ss, name);

            auto value_signed = stoll(size_str);
            current->children[name] = Node{
                .name = name,
                .value = static_cast<make_unsigned_t<long long>>(value_signed),
                .parent = current,
            };
        }
    }

    print_tree(root);

    cout << "\n---\n" << endl;

    unordered_map<Node *, u_int64_t> flat_folder_sizes;
    walk_sum_tree(root, flat_folder_sizes);

    u_int64_t disk_size = 70000000;
    u_int64_t space_needed = 30000000;
    u_int64_t space_used = flat_folder_sizes[&root];
    u_int64_t space_available = disk_size - space_used;
    u_int64_t space_to_free = space_needed - space_available;

    u_int64_t minimal_size_to_free = std::numeric_limits<u_int64_t>::max();
    for (auto &val: flat_folder_sizes) {
        auto size = val.second;
        cout << format("{}: {}", val.first->name, val.second) << endl;

        if (size < space_to_free) continue;
        if (size >= minimal_size_to_free) continue;

        minimal_size_to_free = size;
    }

    cout << "\n---\n" << endl;

    cout << format("Disk capacity:   {}", disk_size) << endl;
    cout << format("Space used:      {}", space_used) << endl;
    cout << format("Space available: {}", space_available) << endl;
    cout << format("Space needed:    {}", space_needed) << endl;
    cout << format("Space to free:   {}", space_to_free) << endl;
    cout << "---" << endl;
    cout << format("Folder size to free: {}", minimal_size_to_free) << endl;
}
