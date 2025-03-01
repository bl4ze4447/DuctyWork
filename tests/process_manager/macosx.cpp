//
// Created by Antonie Gabriel Belu on 01.03.2025.
//

#include "../../process/process_manager.h"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Fill processes should add all running processes to the processes set", "[fill_process_macosx]") {
    process_manager * pm = process_manager::create();
    const process always_present[] = {
        {0, "cron"},
        {0, "kthreadd"},
        {0, "dbus-daemon"}
    };

    const auto plist = pm->get_processes();
    pm->fill_processes();
    REQUIRE(plist.empty() == false);
    REQUIRE(plist.contains(always_present[0]));
    REQUIRE(plist.contains(always_present[1]));
    REQUIRE(plist.contains(always_present[2]));
}