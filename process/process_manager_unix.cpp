//
// Created by Antonie Gabriel Belu on 28.02.2025.
//

#include <filesystem>
#include <fstream>
#include <algorithm>
#include <ranges>

#include "process_manager.h"

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
                        auto view = process_name
                                | std::views::drop_while(isspace)
                                | std::views::reverse
                                | std::views::drop_while(isspace)
                                | std::views::reverse;

                        process_name = std::string(view.begin(), view.end());
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