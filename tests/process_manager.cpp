//
// Created by Antonie Gabriel Belu on 01.03.2025.
//
#include "../process/process_manager.h"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Watch/unwatch should correctly add/remove processes to the watched_processes set", "[watch/unwatch]") {
    process_manager * pm = process_manager::create();
    const process p1(20, "p1.exe"),
                p2(25, "p2.exe"),
                p3(12, "p3.exe");

    pm->watch_process(p1);
    pm->watch_process(p2);
    pm->watch_process(p3);
    REQUIRE(pm->get_watched_processes().contains(p1) == true);
    REQUIRE(pm->get_watched_processes().contains(p2) == true);
    REQUIRE(pm->get_watched_processes().contains(p3) == true);

    pm->unwatch_process(p2);
    REQUIRE(pm->get_watched_processes().contains(p1) == true);
    REQUIRE(pm->get_watched_processes().contains(p2) == false);
    REQUIRE(pm->get_watched_processes().contains(p3) == true);
}

