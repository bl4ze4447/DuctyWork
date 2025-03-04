//
// Created by Antonie Gabriel Belu on 01.03.2025.
//

#include "../../process/process_manager.h"
#include <catch2/catch_test_macros.hpp>
#include <algorithm>

TEST_CASE("Fill processes should add all running processes to the processes set", "[fill_process_unix]") {
    process_manager * pm = process_manager::create();
    const std::string always_present[] = {
        {"[kthreadd]"},
        {"[rcu_sched]"},
        {"[kswapd0]"}
    };

    pm->fill_processes();
    const auto plist = pm->get_processes();

    REQUIRE(plist.empty() == false);
    REQUIRE(std::ranges::any_of(plist.begin(), plist.end(), [&](const process & p) { return p.get_name() == always_present[0];}));
    REQUIRE(std::ranges::any_of(plist.begin(), plist.end(), [&](const process & p) { return p.get_name() == always_present[1];}));
    REQUIRE(std::ranges::any_of(plist.begin(), plist.end(), [&](const process & p) { return p.get_name() == always_present[2];}));
}