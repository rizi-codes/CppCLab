# Compiler and flags
CXX = g++
CC = gcc
CXXFLAGS = -std=c++17 -Wall -Iinclude -g
CFLAGS = -Wall -Iinclude -g
LDFLAGS = -pthread -lgtest -lgtest_main -lbenchmark

# Directories
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
TEST_DIR = tests
BENCH_DIR = benchmarks
BENCH_BIN_DIR = $(BIN_DIR)/benchmarks

# Source and object files (all nested cpp and c)
SRCS = $(shell find $(SRC_DIR) -type f \( -name '*.cpp' -o -name '*.c' \))
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,\
       $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS)))

# Executable names
TARGET = $(BIN_DIR)/app
TEST_TARGET = $(BIN_DIR)/tests

# Benchmark sources and binaries
BENCHMARK_SRCS = $(shell find $(BENCH_DIR) -type f \( -name '*.cpp' -o -name '*.c' \))
BENCHMARK_BINS = $(patsubst $(BENCH_DIR)/%.cpp,$(BENCH_BIN_DIR)/%,\
                  $(patsubst $(BENCH_DIR)/%.c,$(BENCH_BIN_DIR)/%,$(BENCHMARK_SRCS)))

# Main rule
all: format format-check cppcheck $(TARGET) tests benchmarks

# Linking main app
$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

# Compile .cpp files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile .c files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Tests linking rule
tests: $(TEST_TARGET)

$(TEST_TARGET): $(shell find $(TEST_DIR) -type f \( -name '*.cpp' -o -name '*.c' \)) \
                $(filter-out $(SRC_DIR)/main.cpp, $(SRCS))
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

# Benchmark linking rule
benchmarks: $(BENCHMARK_BINS)

$(BENCH_BIN_DIR)/%: $(BENCH_DIR)/%.cpp $(filter-out $(SRC_DIR)/main.cpp,$(SRCS))
	@mkdir -p $(BENCH_BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

$(BENCH_BIN_DIR)/%: $(BENCH_DIR)/%.c $(filter-out $(SRC_DIR)/main.cpp,$(SRCS))
	@mkdir -p $(BENCH_BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

# Format and static check rules
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

# Clean rule
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all clean tests benchmarks format-check cppcheck format
