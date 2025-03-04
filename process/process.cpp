//
// Created by Antonie Gabriel Belu on 20.02.2025.
//

#include "process.h"

bool process::operator==(const process &other) const {
    return this->pid == other.pid && this->name == other.name;
}

bool process::operator<(const process &other) const {
    return this->pid < other.pid;
}

void process::set_pid(const int64_t pid) {
    this->pid = pid;
}
void process::set_name(std::string name) {
    this->name = std::move(name);
}
void process::reset_start_time() {
    this->start_time = std::chrono::system_clock::now();
}

int64_t process::get_pid() const {
    return pid;
}

std::string process::get_name() const {
    return name;
}

std::chrono::time_point<std::chrono::system_clock> process::get_start_time() const {
    return start_time;
}