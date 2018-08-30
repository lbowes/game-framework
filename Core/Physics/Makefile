PROJECT = PhysicsFramework

GCC = gcc
CXX = g++

GLOBAL_INC_OUTPUT_DIR = /home/lbowes/dev/Programming/Deps/Includes/
GLOBAL_LIB_OUTPUT_DIR = /home/lbowes/dev/Programming/Deps/Libs/

INCLUDE_ROOT = ./include/
INCLUDE_DIRS = -I$(INCLUDE_ROOT) -I$(GLOBAL_INC_OUTPUT_DIR)
LIB_DIRS = -L/usr/local/lib/ -L$(GLOBAL_LIB_OUTPUT_DIR)
LOCAL_LIB_OUPTUT_DIR = ./lib/
BUILD_DIR = ./build/
SOURCE_FILES = $(shell find . -name "*.cpp") 
VPATH := $(sort $(dir $(SOURCE_FILES)))
OBJECTS = $(patsubst %.cpp, $(BUILD_DIR)%.o, $(notdir $(SOURCE_FILES)))

CXXFLAGS = $(INCLUDE_DIRS) -MD
LDFLAGS = $(LIB_DIRS)

all: $(PROJECT)

$(BUILD_DIR)%.o: %.cpp
	@echo Compiling $(notdir $<)
	@$(CXX) $(CXXFLAGS) -c -o $@ $< $(LDFLAGS)

$(PROJECT): $(OBJECTS) 
	@ar rvs $(LOCAL_LIB_OUPTUT_DIR)lib$@.a $^
	@cp $(LOCAL_LIB_OUPTUT_DIR)lib$@.a $(GLOBAL_LIB_OUTPUT_DIR)
	@cp -u -a $(INCLUDE_ROOT)/. $(GLOBAL_INC_OUTPUT_DIR)$(PROJECT)

.PHONY: clean

clean:
	@rm -f $(LOCAL_LIB_OUPTUT_DIR)lib$(PROJECT).a $(GLOBAL_LIB_OUTPUT_DIR)lib$(PROJECT).a $(OBJECTS)
	@rm -f $(OBJECTS:.o=.d)
	@echo Cleaned all.

-include $(OBJECTS:.o=.d)