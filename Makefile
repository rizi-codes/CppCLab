# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude -g
LDFLAGS = -pthread -lgtest -lgtest_main

# Directories
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
TEST_DIR = tests

# Source and object files
SRCS = $(wildcard $(SRC_DIR)/*.cpp $(SRC_DIR)/*/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))

# Executable names
TARGET = $(BIN_DIR)/app
TEST_TARGET = $(BIN_DIR)/tests

# Main rule
all: format format-check cppcheck  $(TARGET) tests

# Linking main app
$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Compile .cpp to .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@ 

# Tests linking rule
tests: $(TEST_TARGET)

$(TEST_TARGET): $(wildcard $(TEST_DIR)/**/*.cpp) $(filter-out $(SRC_DIR)/main.cpp, $(wildcard $(SRC_DIR)/*.cpp $(SRC_DIR)/*/*.cpp))
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

# Run clang-format check (no file modifications, just checking)
format-check:
	find src include tests -type f \( -name "*.cpp" -o -name "*.h" \) -not -name ".*" -exec clang-format --dry-run --Werror {} +


# Run cppcheck instead of clang-tidy
cppcheck:
	cppcheck --enable=all --std=c++17 --suppress=missingIncludeSystem --suppress=unusedFunction -Iinclude src


# Automatically fix formatting issues (modifies files)
format:
	find src include tests -type f \( -name "*.cpp" -o -name "*.h" \) -not -name ".*" -exec clang-format -i {} +


# Clean rule
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all clean tests format-check cppcheck format
