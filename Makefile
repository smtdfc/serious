CXX := $(shell command -v g++ || command -v clang++)
CXXFLAGS = -DDEBUG -Wall -Wextra -O2 -std=c++17 -Iinclude

SRC_DIR = src
OBJ_DIR = build
BIN_DIR = bin
BIN_NAME = serious_lang
BUILD_OUT = $(BIN_DIR)/$(BIN_NAME)
INSTALL_DIR = $(HOME)/bin
INSTALL_PATH = $(INSTALL_DIR)/$(BIN_NAME)

SRC := $(shell find $(SRC_DIR) -name '*.cpp')
OBJ := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC))

.PHONY: all run clean install

all: $(BUILD_OUT)

# Compile all object files, then link
$(BUILD_OUT): $(OBJ)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Compile each source file to object
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Install to ~/bin
install: all
	@mkdir -p $(INSTALL_DIR)
	@cp $(BUILD_OUT) $(INSTALL_PATH)
	@chmod +x $(INSTALL_PATH)
	@echo "Installed to $(INSTALL_PATH)"

run: install
	@$(INSTALL_PATH)

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)