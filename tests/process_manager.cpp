//
// Created by Antonie Gabriel Belu on 01.03.2025.
//
#include "../process/process_manager.h"

#include <thread>
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

TEST_CASE("time_check_watched_process should return true if any process has been alived for more than s seconds"
    , "[time_check_watched_processes]") {
    process_manager * pm = process_manager::create();
    const process p1(20, "p1.exe");
    pm->watch_process(p1);

    std::this_thread::sleep_for(std::chrono::milliseconds(1150));
    REQUIRE(pm->time_check_watched_processes(std::chrono::seconds(1)) == true);

    const process p2(25, "p2.exe");
    pm->watch_process(p2);
    std::this_thread::sleep_for(std::chrono::milliseconds(1150));
    REQUIRE(pm->time_check_watched_processes(std::chrono::seconds(2)) == true);

    pm->unwatch_process(p1);
    REQUIRE(pm->time_check_watched_processes(std::chrono::seconds(1)) == true);

    pm->unwatch_process(p2);
    REQUIRE(pm->time_check_watched_processes(std::chrono::seconds(0)) == false);
}

