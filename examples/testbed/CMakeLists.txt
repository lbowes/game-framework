cmake_minimum_required(VERSION 3.17)

project(testbed)

add_library(testbed STATIC
    src/FPVCamera.cpp
    src/main.cpp
    src/PhysicsOverlay.cpp
    src/SteelComposite.cpp
    src/SteelCube.cpp
    src/SteelCubeModel.cpp
    src/Testbed.cpp
)

target_include_directories(testbed PRIVATE
    include/
)