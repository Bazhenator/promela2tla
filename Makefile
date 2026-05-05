CXX      := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -g -O0
BISON    := bison
FLEX     := flex

SRC_DIR   := src
BUILD_DIR := build
BIN       := $(BUILD_DIR)/promela2pluscal

PARSER_C  := $(BUILD_DIR)/parser.cpp
PARSER_H  := $(BUILD_DIR)/parser.hpp
LEXER_C   := $(BUILD_DIR)/lexer.cpp

SRCS := $(SRC_DIR)/main.cpp $(SRC_DIR)/ast.cpp
OBJS := $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o) \
        $(BUILD_DIR)/parser.o $(BUILD_DIR)/lexer.o

.PHONY: all clean test

all: $(BIN)

$(BIN): $(OBJS) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

$(PARSER_C): $(SRC_DIR)/parser.y | $(BUILD_DIR)
	$(BISON) -d -o $(PARSER_C) $<

$(PARSER_H): $(PARSER_C)

$(LEXER_C): $(SRC_DIR)/lexer.l $(PARSER_H) | $(BUILD_DIR)
	$(FLEX) -o $@ $<

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -I$(SRC_DIR) -I$(BUILD_DIR) -c $< -o $@

$(BUILD_DIR)/parser.o: $(PARSER_C) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -I$(SRC_DIR) -I$(BUILD_DIR) -c $< -o $@

$(BUILD_DIR)/lexer.o: $(LEXER_C) $(PARSER_H) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -I$(SRC_DIR) -I$(BUILD_DIR) -Wno-unused-function -c $< -o $@

$(BUILD_DIR)/main.o: $(SRC_DIR)/main.cpp $(PARSER_H) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -I$(SRC_DIR) -I$(BUILD_DIR) -c $< -o $@

$(BUILD_DIR)/ast.o: $(SRC_DIR)/ast.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -I$(SRC_DIR) -I$(BUILD_DIR) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)

test: $(BIN)
	./$(BIN) tests/00_empty.pml