#add_subdirectory(lib/googletest)

include_directories(${LIBRARY_HEADERS_DIR})
#include_directories(lib/googletest/googletest/include)

set(TEST_SOURCE_FILES main.cpp src/test_factorial.cpp)

add_executable(project_tests ${TEST_SOURCE_FILES})
target_link_libraries(project_tests factorial-library) #gtest)
#install(TARGETS project_tests DESTINATION bin)