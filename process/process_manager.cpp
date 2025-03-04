//
// Created by Antonie Gabriel Belu on 20.02.2025.
//

#include "process_manager.h"
#include <algorithm>

void process_manager::watch_process(const process &p) {
    watched_processes.insert(p);
}

void process_manager::unwatch_process(const process &p) {
    watched_processes.erase(p);
}

bool process_manager::time_check_watched_processes(const std::chrono::seconds &s) const {
    const auto now = std::chrono::system_clock::now();
    return std::ranges::any_of(watched_processes, [&now, &s](const process &wp) {
        return std::chrono::duration_cast<std::chrono::seconds>(now - wp.get_start_time()) >= s;
    });
}

const std::set<process> &process_manager::get_watched_processes() const {
    return watched_processes;
}
const std::set<process> &process_manager::get_processes() const {
    return processes;
}

bool process_manager::contains_by_name(const std::set<process> &set, const process &p) {
    return set.find(p) != set.end();
}
