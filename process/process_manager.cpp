//
// Created by Antonie Gabriel Belu on 20.02.2025.
//

#include "process_manager.h"
#include <ranges>
#include <algorithm>

void process_manager::watch_process(const process &p) {
    processes.insert(p);
}

void process_manager::unwatch_process(const process &p) {
    processes.erase(p);
}

bool process_manager::time_check_watched_processes(const std::chrono::seconds &s) const {
    const auto now = std::chrono::system_clock::now();
    return std::ranges::any_of(watched_processes, [&now, &s](const process &wp) {
        return now - wp.get_start_time() >= s;
    });
}

const std::set<process> &process_manager::get_watched_processes() const {
    return watched_processes;
}
const std::set<process> &process_manager::get_processes() const {
    return processes;
}