CXX = g++

CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic

TARGET = build/ctree

SRC_DIR = src
BUILD_DIR = build

TEST_DIR = tests/input
GENERATED_DIR = tests/generated

GENERATOR = scripts/treegen.sh
GENERATED_TEST = $(GENERATED_DIR)/tree-test.in

SRC = $(SRC_DIR)/main.cpp \
      $(SRC_DIR)/Tree.cpp

OBJ = $(SRC:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)


all: $(TARGET)


$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $@


$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)


$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@


run: $(TARGET)
	./$(TARGET)


test: $(TARGET)
	./$(TARGET) < $(TEST_DIR)/basic-tree-test.in


generate:
	mkdir -p $(GENERATED_DIR)
	chmod +x $(GENERATOR)
	$(GENERATOR) 5 3 > $(GENERATED_TEST)
	echo "Generated $(GENERATED_TEST)"


stress-test: $(TARGET) generate
	./$(TARGET) < $(GENERATED_TEST)


clean:
	rm -rf $(BUILD_DIR) $(GENERATED_DIR)


rebuild: clean all


.PHONY: all run test generate stress-test clean rebuild