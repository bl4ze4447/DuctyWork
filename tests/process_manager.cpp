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

    // Watch test
    pm->watch_process(p1);
    pm->watch_process(p2);
    pm->watch_process(p3);
    REQUIRE(pm->get_watched_processes().contains(p1) == true);
    REQUIRE(pm->get_watched_processes().contains(p2) == true);
    REQUIRE(pm->get_watched_processes().contains(p3) == true);

    // Unwatch test
    pm->unwatch_process(p2);
    REQUIRE(pm->get_watched_processes().contains(p1) == true);
    REQUIRE(pm->get_watched_processes().contains(p2) == false);
    REQUIRE(pm->get_watched_processes().contains(p3) == true);
    REQUIRE(pm->get_watched_processes().size() == 2);

    // Unwatching an already unwatched process should not do anything
    pm->unwatch_process(p2);
    REQUIRE(pm->get_watched_processes().size() == 2);

    // Should replace existing p1
    const process p1_pid(20, "p1_new.exe");
    pm->watch_process(p1_pid);
    REQUIRE(process_manager::contains_by_name(pm->get_watched_processes(), p1_pid) == true);
    REQUIRE(process_manager::contains_by_name(pm->get_watched_processes(), p1) == false);
    bool explicit_check = false;
    for (const auto & process : pm->get_watched_processes()) {
        if (process == p1_pid) // do not break, keep going because p1 might be in the set if behaviour is not expected
            explicit_check = true;
        if (process == p1) { // here we break, if we find p1 it means something wrong happened
            explicit_check = false;
            break;
        }
    }

    REQUIRE(explicit_check);
}

TEST_CASE("If any of the watched processes are alive for longer than 's' seconds it should return true"
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

