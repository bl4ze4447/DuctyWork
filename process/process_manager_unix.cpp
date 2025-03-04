//
// Created by Antonie Gabriel Belu on 28.02.2025.
//

#include <filesystem>
#include <fstream>
#include <algorithm>
#include <ranges>

#include "process_manager.h"
#include "string_util.h"

class process_manager_unix final : public process_manager {
public:
    void fill_processes() override {
        processes.clear();
        for (const std::filesystem::directory_entry& dir_entry
            : std::filesystem::directory_iterator("/proc")) {

            if (const std::string process_dir = dir_entry.path().filename().string();
                std::ranges::all_of(process_dir, ::isdigit)) {

                std::ifstream file("/proc/" + process_dir + "/status");
                if (!file)
                    continue;

                std::string line, process_name;
                bool running = false;
                while (std::getline(file, line)) {
                    if (line.starts_with("Name:")) {
                        process_name = line.substr(5); // skip Name:
                        ltrim(process_name);
                        rtrim(process_name);
                    }
                    else if (line.starts_with("State:")) {
                        running = line.find('R') != std::string::npos;
                        break;
                    }
                }

                if (running)
                    processes.insert({std::stoi(process_dir), process_name});
            }
        }
    }
};

process_manager * process_manager::create() {
    return new process_manager_unix();
}