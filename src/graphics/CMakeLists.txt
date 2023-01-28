project(game-framework-graphics)

ADD_LIBRARY(game-framework-graphics STATIC
    src/utils/Logger.cpp
)

target_include_directories(game-framework-graphics PRIVATE
    include/
)

# temp - only for testing initial cmake setup
SET(APP_EXE StaticTest)
ADD_EXECUTABLE(${APP_EXE} test_static_lib.cpp)
TARGET_LINK_LIBRARIES(${APP_EXE} game-framework-graphics)