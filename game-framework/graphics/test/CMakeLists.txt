#add_subdirectory(lib/googletest)

include_directories(${GRAPHICS_HEADERS_DIR})
#include_directories(lib/googletest/googletest/include)

set(GRAPHICS_TEST_SRC
    main.cpp
    src/test_factorial.cpp
)

add_executable(graphics-tests ${GRAPHICS_TEST_SRC})
target_link_libraries(graphics-tests game-framework-graphics) #gtest)
#install(TARGETS project_tests DESTINATION bin)