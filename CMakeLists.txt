cmake_minimum_required(VERSION 3.30)
project(DuctyWork)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC OFF) # CMAKE_AUTOUIC causing issues on Ubuntu
set(Qt6_DIR "/Users/bl4ze/Qt/6.8.2/macos/lib/cmake/Qt6/")

# Used for Catch2 fetching
include(FetchContent)
include_directories(DuctyWork windows/ build/)

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED
)

# Main app source files
set(SOURCES main.cpp
        process/process.cpp
        process/process.h
        process/process_manager.cpp
        process/process_manager.h
        windows/mainwindow.cpp
        windows/mainwindow.h
)

# Platform dependent sources go in here
if(WIN32)
    list(APPEND SOURCES process/process_manager_win32.cpp)
elseif (APPLE)
    list(APPEND SOURCES process/process_manager_macosx.cpp)
elseif (UNIX)
    list(APPEND SOURCES process/process_manager_unix.cpp)
endif()

# Generate UI headers and add them to SOURCES
qt6_wrap_ui(UI_HEADERS windows/mainwindow.ui)
list(APPEND SOURCES ${UI_HEADERS})

add_executable(DuctyWork ${SOURCES})
target_link_libraries(DuctyWork
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
)

# Tests
FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.5.2
)
FetchContent_MakeAvailable(Catch2)
enable_testing()

set(TEST_SOURCES tests/process_manager.cpp)

# Platform dependent tests go in here
if(WIN32)
    list(APPEND TEST_SOURCES tests/process_manager/win32.cpp)
elseif (APPLE)
    list(APPEND TEST_SOURCES tests/process_manager/macosx.cpp)
elseif (UNIX)
    list(APPEND TEST_SOURCES tests/process_manager/unix.cpp)
endif()

add_executable(Tests ${SOURCES} ${TEST_SOURCES})
target_link_libraries(Tests PRIVATE Catch2::Catch2)

include(Catch)
catch_discover_tests(Tests)