# Compiler and flags
CXX        = g++
CC         = gcc
CXXFLAGS   = -std=c++17 -Wall -Iinclude -I$(TEST_DIR) -g
CFLAGS     = -Wall -Iinclude -I$(TEST_DIR) -g
LDFLAGS    = -pthread -lbenchmark

# Directories
SRC_DIR       = src
OBJ_DIR       = obj
BIN_DIR       = bin
TEST_DIR      = tests
BENCH_DIR     = benchmarks
BENCH_BIN_DIR = $(BIN_DIR)/benchmarks

# Source and object files under src/
SRCS = $(shell find $(SRC_DIR) -type f \( -name '*.cpp' -o -name '*.c' \))
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,\
       $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS)))

# Executable names
TARGET         = $(BIN_DIR)/app
GTEST_TARGET   = $(BIN_DIR)/gtest_tests
CHECK_TARGET   = $(BIN_DIR)/check_tests

# GoogleTest (C++) test files
GTEST_SRCS := $(shell find $(TEST_DIR) -type f -name '*.cpp')

# Check (C) test files (named test_*.c)
CHECK_SRCS := $(shell find $(TEST_DIR) -type f -name 'test_*.c')

# Linker flags for Check
CHECK_LDFLAGS = -pthread -lcheck -lsubunit -lm

# -----------------------------------------------------------------------------
# Main rule
# -----------------------------------------------------------------------------
all: format format-check cppcheck $(TARGET) tests benchmarks

# -----------------------------------------------------------------------------
# Build the main application
# -----------------------------------------------------------------------------
$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

# Compile .cpp sources
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile .c sources
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# -----------------------------------------------------------------------------
# Tests: both GoogleTest and Check
# -----------------------------------------------------------------------------
tests: gtest_tests check_tests

# 1) GoogleTest C++ tests
gtest_tests: $(GTEST_TARGET)

$(GTEST_TARGET): $(GTEST_SRCS) $(filter-out $(SRC_DIR)/main.cpp,$(SRCS))
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@ -pthread -lgtest -lgtest_main

# 2) Check C tests
check_tests: $(CHECK_TARGET)

$(CHECK_TARGET): $(CHECK_SRCS) $(filter-out $(SRC_DIR)/main.cpp,$(SRCS))
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS) $(CHECK_LDFLAGS)

# -----------------------------------------------------------------------------
# Build benchmarks
# -----------------------------------------------------------------------------
benchmarks: $(BENCHMARK_BINS)

# C++ benchmarks
$(BENCH_BIN_DIR)/%: $(BENCH_DIR)/%.cpp $(filter-out $(SRC_DIR)/main.cpp,$(SRCS))
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

# C benchmarks
$(BENCH_BIN_DIR)/%: $(BENCH_DIR)/%.c $(filter-out $(SRC_DIR)/main.cpp,$(SRCS))
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

# -----------------------------------------------------------------------------
# Formatting & static checks
# -----------------------------------------------------------------------------
format-check:
	find src include tests benchmarks -type f \( -name "*.cpp" -o -name "*.h" -o -name "*.c" \) \
	  -exec clang-format --dry-run --Werror {} +

cppcheck:
	find src -type f \( -name '*.cpp' -o -name '*.c' \) -exec \
	  cppcheck --enable=all --std=c++17 --suppress=missingIncludeSystem \
	           --suppress=unusedFunction -Iinclude {} +

format:
	find src include tests benchmarks -type f \( -name "*.cpp" -o -name "*.h" -o -name "*.c" \) \
	  -exec clang-format -i {} +

# -----------------------------------------------------------------------------
# Clean
# -----------------------------------------------------------------------------
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all clean tests gtest_tests check_tests benchmarks format-check cppcheck format
