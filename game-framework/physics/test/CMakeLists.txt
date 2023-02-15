#add_subdirectory(lib/googletest)

include_directories(${PHYSICS_HEADERS_DIR})
#include_directories(lib/googletest/googletest/include)

set(TEST_SOURCE_FILES
    main.cpp
    src/test_some_physics.cpp
)

add_executable(physics-tests ${TEST_SOURCE_FILES})
target_link_libraries(physics-tests game-framework-physics) #gtest)
#install(TARGETS project_tests DESTINATION bin)