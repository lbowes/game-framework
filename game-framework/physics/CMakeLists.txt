set(PHYSICS_SRC
    src/RigidBodyStateSnapshot.cpp
    src/State.cpp
    src/RigidBodyGroup.cpp
    src/RigidBody.cpp
    src/RigidBodyGroupMember.cpp
    src/CoordTransform3D.cpp
    src/Mass.cpp
    src/InertiaTensor.cpp
)

add_library(game-framework-physics STATIC ${PHYSICS_SRC})
target_include_directories(game-framework-physics PRIVATE include/)
set(PHYSICS_HEADERS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Tests
add_subdirectory(test)