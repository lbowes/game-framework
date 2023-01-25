PROJECT = Testbed

GCC = gcc
CXX = g++

LOCAL_OUTPUT_DIR = ./bin/

INCLUDE_DIRS = -I/home/lbowes/dev/Programming/Deps/Includes/
LIB_DIRS = -L/home/lbowes/dev/Programming/Deps/Libs/
BUILD_DIR = ./build/
SOURCE_FILES = $(shell find . -name "*.cpp")
VPATH := $(sort $(dir $(SOURCE_FILES))) 
OBJECTS = $(patsubst %.cpp, $(BUILD_DIR)%.o, $(notdir $(SOURCE_FILES)))

CXXFLAGS = -Wall -Wextra $(INCLUDE_DIRS) -MD
LDFLAGS = $(LIB_DIRS) -lGraphicsFramework -lPhysicsFramework $(shell pkg-config --libs --static glfw3) $(shell pkg-config --libs --static glew)

all: $(LOCAL_OUTPUT_DIR)$(PROJECT)

run: $(LOCAL_OUTPUT_DIR)$(PROJECT)
	./$<

$(BUILD_DIR)%.o: %.cpp
	@echo Compiling $(notdir $<)
	@$(CXX) $(CXXFLAGS) -c -o $@ $< $(LDFLAGS)

$(LOCAL_OUTPUT_DIR)$(PROJECT): $(OBJECTS)
	@$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

.PHONY: clean

clean:
	@rm -f $(LOCAL_OUTPUT_DIR)$(PROJECT) $(OBJECTS)
	@rm -f $(OBJECTS:.o=.d)
	@echo Cleaned all.

-include $(OBJECTS:.o=.d)