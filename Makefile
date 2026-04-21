CXX = clang++
CXXFLAGS = -std=c++17 -Wall -Iinclude -I/opt/homebrew/include
LDFLAGS = -lcurl

SRC_DIR = src
BUILD_DIR = build

# Cerca TUTTI i .cpp ricorsivamente
SRC = $(shell find $(SRC_DIR) -name '*.cpp')

# Converte src/.../file.cpp → build/.../file.o
OBJ = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRC))

TARGET = route_optimizer

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET) $(LDFLAGS)

# Regola generica per compilare qualsiasi .cpp in qualsiasi sottocartella
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(TARGET)
