cmake_minimum_required(VERSION 3.30)
project(DuctyWork)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(Qt6_DIR "/Users/bl4ze/Qt/6.8.2/macos/lib/cmake/Qt6/")

find_package(Qt6 COMPONENTS
  Core
  Gui
  Widgets
  REQUIRED)

include_directories(DuctyWork "windows/")

set(SOURCES main.cpp
        windows/mainwindow.cpp
        windows/mainwindow.h
        windows/mainwindow.ui
        process/process.cpp
        process/process.h
        process/process_manager.cpp
        process/process_manager.h
)

if(WIN32)
    list(APPEND SOURCES process/process_manager_win32.cpp)
elseif (APPLE)
    list(APPEND SOURCES process/process_manager_macosx.cpp)
elseif (UNIX)
    list(APPEND SOURCES process/process_manager_unix.cpp)
endif()

add_executable(DuctyWork ${SOURCES})

target_link_libraries(DuctyWork
  Qt6::Core
  Qt6::Gui
  Qt6::Widgets
)

