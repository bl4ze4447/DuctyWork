//
// Created by Antonie Gabriel Belu on 01.03.2025.
//

#include "../../process/process_manager.h"
#include <catch2/catch_test_macros.hpp>
#include <algorithm>

TEST_CASE("Fill processes should add all running processes to the processes set", "[fill_process_unix]") {
    process_manager * pm = process_manager::create();
    pm->fill_processes();
    const auto plist = pm->get_processes();
    REQUIRE(plist.empty() == false);
    for (const auto & p : plist) {
        INFO(p.get_name() << '\n');
        CHECK(FALSE);
    }
}