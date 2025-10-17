cmake_minimum_required(VERSION 4.0)
project(gameoflife C)

set(CMAKE_C_STANDARD 23)

find_package(SDL3 REQUIRED)
include_directories(${SDL3_INCLUDE_DIRS})

set(SOURCES src/main.c
        src/window.c
        src/window.h
        src/util.h
        src/model.c
        src/model.h
        src/game.c
        src/game.h)
add_executable(gameoflife ${SOURCES})
target_link_libraries(gameoflife SDL3::SDL3)

install(TARGETS gameoflife)
