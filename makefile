# DIGITZ BUILD SYSTEM - Enhanced with Consciousness Modules

# Directories
TARGET := output/digitz
SRC := src/
OBJ := obj/
OUTPUT_DIR := output/

# Compiler settings
CXX := clang++
CXXFLAGS := -std=c++23 -O3 -pthread -march=native -Wall -Wextra
LDFLAGS := -lncurses -lcurl -lm

# Source files
MAIN_SRC := $(SRC)main.cpp
MODULE_SRCS := $(SRC)language_module.cpp \
               $(SRC)consciousness_module.cpp \
               $(SRC)metacognition_module.cpp \
               $(SRC)module_integration.cpp

# All source files
SRCS := $(MAIN_SRC) $(MODULE_SRCS)

# Object files (mirror source structure in obj/)
OBJS := $(patsubst $(SRC)%.cpp,$(OBJ)%.o,$(SRCS))

# Header files for dependency tracking
HEADERS := $(SRC)uac.h \
           $(SRC)language_module.h \
           $(SRC)consciousness_module.h \
           $(SRC)embodiment_module.h \
           $(SRC)metacognition_module.h \
           $(SRC)module_integration.h

# Colors for output
COLOR_RESET := \033[0m
COLOR_BOLD := \033[1m
COLOR_GREEN := \033[32m
COLOR_BLUE := \033[34m
COLOR_YELLOW := \033[33m

# Default target
.DEFAULT_GOAL := all

# Phony targets
.PHONY: all clean rebuild run debug release modules help install

# Main build target
all: $(TARGET)
	@echo "$(COLOR_GREEN)$(COLOR_BOLD)✓ Build complete!$(COLOR_RESET)"
	@echo "$(COLOR_BLUE)Run with: ./$(TARGET)$(COLOR_RESET)"

# Link executable
$(TARGET): $(OBJS) | $(OUTPUT_DIR)
	@echo "$(COLOR_YELLOW)Linking $(TARGET)...$(COLOR_RESET)"
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET) $(LDFLAGS)

# Compile main source
$(OBJ)main.o: $(SRC)main.cpp $(HEADERS) | $(OBJ)
	@echo "$(COLOR_BLUE)Compiling main.cpp...$(COLOR_RESET)"
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile module sources
$(OBJ)language_module.o: $(SRC)language_module.cpp $(SRC)language_module.h | $(OBJ)
	@echo "$(COLOR_BLUE)Compiling language_module.cpp...$(COLOR_RESET)"
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ)consciousness_module.o: $(SRC)consciousness_module.cpp $(SRC)consciousness_module.h | $(OBJ)
	@echo "$(COLOR_BLUE)Compiling consciousness_module.cpp...$(COLOR_RESET)"
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ)embodiment_module.o: $(SRC)embodiment_module.cpp $(SRC)embodiment_module.h | $(OBJ)
	@echo "$(COLOR_BLUE)Compiling embodiment_module.cpp...$(COLOR_RESET)"
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ)metacognition_module.o: $(SRC)metacognition_module.cpp $(SRC)metacognition_module.h | $(OBJ)
	@echo "$(COLOR_BLUE)Compiling metacognition_module.cpp...$(COLOR_RESET)"
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ)module_integration.o: $(SRC)module_integration.cpp $(SRC)module_integration.h | $(OBJ)
	@echo "$(COLOR_BLUE)Compiling module_integration.cpp...$(COLOR_RESET)"
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Create directories
$(OBJ):
	@mkdir -p $(OBJ)

$(OUTPUT_DIR):
	@mkdir -p $(OUTPUT_DIR)

# Clean build artifacts
clean:
	@echo "$(COLOR_YELLOW)Cleaning build artifacts...$(COLOR_RESET)"
	@rm -rf $(OBJ) $(OUTPUT_DIR)
	@echo "$(COLOR_GREEN)✓ Clean complete$(COLOR_RESET)"

# Rebuild from scratch
rebuild: clean all

# Run the program
run: $(TARGET)
	@echo "$(COLOR_GREEN)$(COLOR_BOLD)Starting DIGITZ...$(COLOR_RESET)"
	@./$(TARGET)

# Debug build (with symbols, no optimization)
debug: CXXFLAGS := -std=c++23 -g -O0 -pthread -rdynamic -march=native -Wall -Wextra -DDEBUG
debug: clean all
	@echo "$(COLOR_GREEN)$(COLOR_BOLD)✓ Debug build complete$(COLOR_RESET)"

# Release build (maximum optimization)
release: CXXFLAGS := -std=c++23 -O3 -pthread -rdynamic -march=native -flto -DNDEBUG
release: clean all
	@strip $(TARGET)
	@echo "$(COLOR_GREEN)$(COLOR_BOLD)✓ Release build complete (stripped)$(COLOR_RESET)"

# Build only the consciousness modules
modules: $(OBJ)language_module.o \
         $(OBJ)consciousness_module.o \
         $(OBJ)embodiment_module.o \
         $(OBJ)metacognition_module.o \
         $(OBJ)module_integration.o
	@echo "$(COLOR_GREEN)✓ Consciousness modules compiled$(COLOR_RESET)"

# Install to system (optional)
install: release
	@echo "$(COLOR_YELLOW)Installing to /usr/local/bin...$(COLOR_RESET)"
	@sudo cp $(TARGET) /usr/local/bin/digitz
	@sudo chmod +x /usr/local/bin/digitz
	@echo "$(COLOR_GREEN)✓ Installed! Run with: digitz$(COLOR_RESET)"

# Help target
help:
	@echo "$(COLOR_BOLD)DIGITZ Build System - Available Targets:$(COLOR_RESET)"
	@echo ""
	@echo "  $(COLOR_GREEN)make$(COLOR_RESET) or $(COLOR_GREEN)make all$(COLOR_RESET)     - Build the project"
	@echo "  $(COLOR_GREEN)make run$(COLOR_RESET)              - Build and run DIGITZ"
	@echo "  $(COLOR_GREEN)make clean$(COLOR_RESET)            - Remove build artifacts"
	@echo "  $(COLOR_GREEN)make rebuild$(COLOR_RESET)          - Clean and rebuild"
	@echo "  $(COLOR_GREEN)make debug$(COLOR_RESET)            - Build with debug symbols"
	@echo "  $(COLOR_GREEN)make release$(COLOR_RESET)          - Build optimized release"
	@echo "  $(COLOR_GREEN)make modules$(COLOR_RESET)          - Build only consciousness modules"
	@echo "  $(COLOR_GREEN)make install$(COLOR_RESET)          - Install to /usr/local/bin"
	@echo "  $(COLOR_GREEN)make help$(COLOR_RESET)             - Show this help message"
	@echo ""
	@echo "$(COLOR_BOLD)Module Files:$(COLOR_RESET)"
	@echo "  • language_module.cpp      - N-grams, Markov chains"
	@echo "  • consciousness_module.cpp - IIT, Global Workspace"
	@echo "  • embodiment_module.cpp    - Grounding, Qualia"
	@echo "  • metacognition_module.cpp - Self-model, Dreams"
	@echo "  • module_integration.cpp   - Integration layer"
	@echo ""
	@echo "$(COLOR_BOLD)Build Flags:$(COLOR_RESET)"
	@echo "  CXX=$(CXX)"
	@echo "  CXXFLAGS=$(CXXFLAGS)"
	@echo "  LDFLAGS=$(LDFLAGS)"
	@echo ""

# Dependency tracking (auto-regenerate if headers change)
-include $(OBJS:.o=.d)

$(OBJ)%.o: $(SRC)%.cpp
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@
