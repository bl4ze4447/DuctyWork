//
// Created by Antonie Gabriel Belu on 01.03.2025.
//

#include "../../process/process_manager.h"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Fill processes should add all running processes to the processes set", "[fill_process_win32]") {
    const process_manager * pm = process_manager::create();
    const process always_present[] = {
        {0, "smss.exe"},
        {0, "csrss.exe"},
        {0, "svchost.exe"}
    };

    const auto plist = pm->get_processes();
    REQUIRE(plist.empty() == false);
    REQUIRE(plist.contains(always_present[0]));
    REQUIRE(plist.contains(always_present[1]));
    REQUIRE(plist.contains(always_present[2]));
}