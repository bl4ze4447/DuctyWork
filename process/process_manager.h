//
// Created by Antonie Gabriel Belu on 20.02.2025.
//

#ifndef PROCESS_MANAGER_H
#define PROCESS_MANAGER_H

#include <set>
#include "process.h"

class process_manager {
protected:
    std::set<process>       watched_processes{};
    std::set<process>       processes{};
public:
    virtual ~process_manager() = default;
    process_manager() = default;
    static process_manager * create();

    virtual void fill_processes() = 0;
    void watch_process(const process &p);
    void unwatch_process(const process &p);
    [[nodiscard]] bool time_check_watched_processes(const std::chrono::seconds &s) const;
    [[nodiscard]] const std::set<process> &get_watched_processes() const;
    [[nodiscard]] const std::set<process> &get_processes() const;
};



#endif //PROCESS_MANAGER_H
