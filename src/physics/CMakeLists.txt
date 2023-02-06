cmake_minimum_required(VERSION 3.17)

project(game-framework-physics)

add_library(game-framework-physics STATIC
    src/RigidBodyStateSnapshot.cpp
    src/State.cpp
    src/RigidBodyGroup.cpp
    src/RigidBody.cpp
    src/RigidBodyGroupMember.cpp
    src/CoordTransform3D.cpp
    src/Mass.cpp
    src/InertiaTensor.cpp
)

target_include_directories(game-framework-physics PRIVATE
    include/
)