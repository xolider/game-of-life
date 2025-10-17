cmake_minimum_required(VERSION 4.0)
project(gameoflife VERSION 1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 23)

find_package(SDL3 REQUIRED)
find_package(SDL3_ttf REQUIRED)
include_directories(${SDL3_INCLUDE_DIRS} ${SDL3_ttf_INCLUDE_DIRS})

set(SOURCES src/main.c
        src/window.c
        src/window.h
        src/util.h
        src/model.c
        src/model.h
        src/game.c
        src/game.h)
add_executable(gameoflife ${SOURCES})
target_link_libraries(gameoflife PRIVATE SDL3::SDL3 SDL3_ttf::SDL3_ttf)
target_compile_definitions(gameoflife PRIVATE ROBOTO_TTF_PATH="${ROBOTO_TTF_PATH}")

install(TARGETS gameoflife)
