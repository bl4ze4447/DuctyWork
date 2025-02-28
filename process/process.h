//
// Created by Antonie Gabriel Belu on 20.02.2025.
//

#ifndef PROCESS_H
#define PROCESS_H
#include <cstdint>
#include <string>
#include <chrono>

class process {
protected:
    int64_t                                             pid;
    std::string                                         name;
    std::chrono::time_point<std::chrono::system_clock>  start_time;
public:
    process(const int64_t pid, std::string name)
    : pid(pid), name(std::move(name)), start_time(std::chrono::system_clock::now()) {}

    bool operator==(const process &other) const;
    bool operator<(const process &other) const; // for set

    void set_pid(int64_t pid);
    void set_name(std::string name);
    void reset_start_time();
    [[nodiscard]] int64_t get_pid() const ;
    [[nodiscard]] std::string get_name() const;
    [[nodiscard]] std::chrono::time_point<std::chrono::system_clock> get_start_time() const;
};



#endif //PROCESS_H
