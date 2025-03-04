//
// Created by Antonie Gabriel Belu on 28.02.2025.
//

#include <filesystem>
#include <fstream>
#include <algorithm>
#include <ranges>

#include "process_manager.h"
#include "string_utils.h"

class process_manager_unix final : public process_manager {
public:
    void fill_processes() override {
        processes.clear();
        for (const std::filesystem::directory_entry& dir_entry
            : std::filesystem::directory_iterator("/proc")) {

            if (const std::string process_dir = dir_entry.path().filename().string();
                std::ranges::all_of(process_dir, ::isdigit)) {

                std::ifstream proc_pid_stat("/proc/" + process_dir + "/stat");
                if (!proc_pid_stat)
                    continue;

                std::string ignore, line, process_name;
                char state;
                proc_pid_stat >> ignore >> process_name >> state;
                proc_pid_stat.close();

                if (process_name.size() < 2) continue;
                process_name = process_name.substr(1, process_name.size() - 2); // parantheses

                if (state == 'R')
                    processes.insert({std::stoi(process_dir), process_name});
            }
        }
    }
};

process_manager * process_manager::create() {
    return new process_manager_unix();
}