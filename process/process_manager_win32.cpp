//
// Created by Antonie Gabriel Belu on 28.02.2025.
//

#include <windows.h>
#include <tlhelp32.h>
#include <stringapiset.h>

#include "process_manager.h"

class process_manager_win32 : public process_manager {
    HANDLE                  snapshot{};
    PROCESSENTRY32W         process_entry{};
    void convert_wide_to_utf8(const std::wstring& wide, std::string& utf8) {
        if(wide.empty()) {
          utf8.clear();
          return;
        }

        int unicode_chars = WideCharToMultiByte(
            CP_UTF8,
            0,
            &wide[0],
            static_cast<int>(wide.size()),
            nullptr,
            0,
            nullptr,
            nullptr
        );

        utf8.resize(unicode_chars);
        WideCharToMultiByte(
            CP_UTF8,
            0,
            &wide[0],
            static_cast<int>(wide.size()),
            &utf8[0],
            unicode_chars,
            nullptr,
            NULL
        );
    }
public:
    void fill_processes() override {
        processes.clear();
        process_entry = {};
        process_entry.dwSize = sizeof(PROCESSENTRY32W);

        snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        if (snapshot == INVALID_HANDLE_VALUE)
            return;

        if (Process32FirstW(snapshot, &process_entry) == FALSE) {
            CloseHandle(snapshot);
            return;
        }

        std::string process_name;
        while (Process32NextW(snapshot, &process_entry)) {
            convert_wide_to_utf8(process_entry.szExeFile, process_name);
            processes.insert({process_entry.th32ProcessID, process_name});
        }

        CloseHandle(snapshot);
    }
};

process_manager * process_manager::create() {
    return new process_manager_win32();
}