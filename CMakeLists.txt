cmake_minimum_required(VERSION 3.17)
project(game-framework)

set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})

add_subdirectory(game-framework/graphics)
add_subdirectory(game-framework/physics)