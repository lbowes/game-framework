set(GRAPHICS_SRC src/factorial.cpp)
add_library(game-framework-graphics STATIC ${GRAPHICS_SRC})
target_include_directories(game-framework-graphics PRIVATE include/)

set(GRAPHICS_HEADERS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Tests
add_subdirectory(test)