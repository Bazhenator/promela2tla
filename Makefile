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
OBJS = build/main.o build/ast.o build/parser.o build/lexer.o \
       build/typedef_table.o build/symbol_table.o build/resolver.o \
       build/type_check.o build/pipeline.o

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

build/typedef_table.o: src/typedef_table.cpp src/typedef_table.h
	$(CXX) $(CXXFLAGS) -Isrc -Ibuild -c src/typedef_table.cpp -o build/typedef_table.o

build/symbol_table.o: src/symbol_table.cpp src/symbol_table.h src/ast.h
	$(CXX) $(CXXFLAGS) -Isrc -Ibuild -c src/symbol_table.cpp -o build/symbol_table.o

build/resolver.o: src/resolver.cpp src/resolver.h src/symbol_table.h src/ast.h
	$(CXX) $(CXXFLAGS) -Isrc -Ibuild -c src/resolver.cpp -o build/resolver.o

build/type_check.o: src/type_check.cpp src/type_check.h src/ast.h
	$(CXX) $(CXXFLAGS) -Isrc -Ibuild -c src/type_check.cpp -o build/type_check.o

build/pipeline.o: src/pipeline.cpp src/pipeline.h src/ast.h \
                  src/resolver.h src/type_check.h src/parser_types.h
	$(CXX) $(CXXFLAGS) -Isrc -Ibuild -c src/pipeline.cpp -o build/pipeline.o