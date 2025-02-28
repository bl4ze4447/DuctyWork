//
// Created by Antonie Gabriel Belu on 28.02.2025.
//


#include	<sys/user.h>

#include "process_manager.h"

class process_manager_macosx final : public process_manager {
    int                     mib[3] = {CTL_KERN, KERN_PROC, KERN_PROC_ALL};
    kinfo_proc *            process_list{};
    size_t                  process_count{};
public:
    void fill_processes() override {
        processes.clear();
        if (sysctl(mib, 3, nullptr, &process_count, nullptr, 0) == -1)
            return;

        process_list = new kinfo_proc[process_count / sizeof(kinfo_proc)];
        if (sysctl(mib, 3, process_list, &process_count, nullptr, 0) == -1)
            return;

        process_count = process_count / sizeof(kinfo_proc);
        for (size_t i = 0; i < process_count; i++)
            processes.insert({process_list[i].kp_proc.p_pid, process_list[i].kp_proc.p_comm});

        delete[] process_list;
    }
};

process_manager * process_manager::create() {
    return new process_manager_macosx();
}