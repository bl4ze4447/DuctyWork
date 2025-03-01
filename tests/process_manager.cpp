//
// Created by Antonie Gabriel Belu on 01.03.2025.
//
#include "../process/process_manager.h"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Watching/unwatching a process should add/remove it to/from watched_processes", "[watch_process/unwatch_process]") {
    process_manager * pm = process_manager::create();
    const process test_proc(20, "test_proc.exe");
    pm->watch_process(test_proc);
    REQUIRE(pm->get_watched_processes().contains(test_proc) == true);

    pm->unwatch_process(test_proc);
    REQUIRE(pm->get_watched_processes().contains(test_proc) == false);
}

