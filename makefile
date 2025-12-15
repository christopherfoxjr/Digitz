# Nexus' BUILD SYSTEM - Cross-compile to Windows using Zig (no MinGW needed)

# Build target selection
# Usage: make TARGET_OS=windows (cross-compile to Windows using Zig)
#        make                   (native Linux build)
TARGET_OS ?= linux

# Directories
SRC := src/
OBJ := obj/
OUTPUT_DIR := output/

# Platform-specific settings
ifeq ($(TARGET_OS),windows)
    # Cross-compilation to Windows using Zig
    TARGET := $(OUTPUT_DIR)Nexus.exe
    ZIG := zig
    CXX := zig cc
    # Use c++2b (C++23 draft) - Zig doesn't recognize c++23 yet
    # Add -DNO_CURSES to disable ncurses (Windows doesn't have it)
    CXXFLAGS := -std=c++2b -O3 -target x86_64-windows-gnu -DWINDOWS_BUILD -DNO_CURSES
    # Minimal libs - no pdcurses or curl for basic build
    LDFLAGS := -lws2_32
    OBJ_EXT := .obj
    PLATFORM_NAME := Windows (Zig cross-compile)
    USE_ZIG := 1
else
    # Native Linux build
    TARGET := $(OUTPUT_DIR)Nexus
    CXX := clang++
    # Try c++23, fallback to c++2b if not supported
    CXXFLAGS := -std=c++23 -O3 -pthread -march=native -Wall -Wextra
    LDFLAGS := -lncurses -lcurl -lm
    OBJ_EXT := .o
    PLATFORM_NAME := Linux (native)
    USE_ZIG := 0
endif

# Source files
MAIN_SRC := $(SRC)main.cpp
MODULE_SRCS := $(SRC)language_module.cpp \
               $(SRC)consciousness_module.cpp \
               $(SRC)metacognition_module.cpp \
               $(SRC)module_integration.cpp

# All source files
SRCS := $(MAIN_SRC) $(MODULE_SRCS)

# Object files
OBJS := $(patsubst $(SRC)%.cpp,$(OBJ)%$(OBJ_EXT),$(SRCS))

# Header files
HEADERS := $(SRC)uac.h \
           $(SRC)language_module.h \
           $(SRC)consciousness_module.h \
           $(SRC)embodiment_module.h \
           $(SRC)metacognition_module.h \
           $(SRC)module_integration.h

# Colors
COLOR_RESET := \033[0m
COLOR_BOLD := \033[1m
COLOR_GREEN := \033[32m
COLOR_BLUE := \033[34m
COLOR_YELLOW := \033[33m
COLOR_CYAN := \033[36m
COLOR_MAGENTA := \033[35m

.DEFAULT_GOAL := all

.PHONY: all clean rebuild run debug release modules help install windows linux check-deps install-zig

# Main build target
all: check-deps $(TARGET)
	@echo "$(COLOR_GREEN)$(COLOR_BOLD)✓ Build complete for $(PLATFORM_NAME)!$(COLOR_RESET)"
	@echo "$(COLOR_BLUE)Executable: $(TARGET)$(COLOR_RESET)"
ifeq ($(TARGET_OS),windows)
	@echo "$(COLOR_CYAN)Transfer to Windows and run with: Nexus.exe$(COLOR_RESET)"
	@echo "$(COLOR_YELLOW)Note: You may need to bundle Windows libraries with the .exe$(COLOR_RESET)"
endif

# Check for cross-compilation dependencies
check-deps:
ifeq ($(TARGET_OS),windows)
	@echo "$(COLOR_CYAN)Checking for Zig compiler...$(COLOR_RESET)"
	@which $(ZIG) > /dev/null 2>&1 || (echo "$(COLOR_YELLOW)ERROR: Zig not found!$(COLOR_RESET)" && \
	 echo "$(COLOR_GREEN)Install Zig easily:$(COLOR_RESET)" && \
	 echo "  $(COLOR_CYAN)make install-zig$(COLOR_RESET)  (installs Zig to ~/.local)" && \
	 echo "" && \
	 echo "Or manually:" && \
	 echo "  $(COLOR_CYAN)curl -L https://ziglang.org/download/0.11.0/zig-linux-x86_64-0.11.0.tar.xz | tar -xJ$(COLOR_RESET)" && \
	 echo "  $(COLOR_CYAN)sudo mv zig-linux-x86_64-0.11.0 /opt/zig$(COLOR_RESET)" && \
	 echo "  $(COLOR_CYAN)sudo ln -s /opt/zig/zig /usr/local/bin/zig$(COLOR_RESET)" && exit 1)
	@echo "$(COLOR_GREEN)✓ Zig compiler found$(COLOR_RESET)"
endif

# Install Zig locally (no sudo needed)
install-zig:
	@echo "$(COLOR_CYAN)Installing Zig to ~/.local/bin...$(COLOR_RESET)"
	@mkdir -p ~/.local/bin ~/.local/zig
	@echo "$(COLOR_YELLOW)Downloading Zig 0.11.0...$(COLOR_RESET)"
	@curl -L https://ziglang.org/download/0.11.0/zig-linux-x86_64-0.11.0.tar.xz -o /tmp/zig.tar.xz
	@tar -xf /tmp/zig.tar.xz -C ~/.local/zig --strip-components=1
	@ln -sf ~/.local/zig/zig ~/.local/bin/zig
	@rm /tmp/zig.tar.xz
	@echo "$(COLOR_GREEN)✓ Zig installed!$(COLOR_RESET)"
	@echo "$(COLOR_YELLOW)Add to PATH: export PATH=\$$HOME/.local/bin:\$$PATH$(COLOR_RESET)"
	@echo "$(COLOR_YELLOW)Or add to ~/.bashrc: echo 'export PATH=\$$HOME/.local/bin:\$$PATH' >> ~/.bashrc$(COLOR_RESET)"

# Quick target aliases
windows:
	@$(MAKE) TARGET_OS=windows

linux:
	@$(MAKE) TARGET_OS=linux

# Link executable
$(TARGET): $(OBJS) | $(OUTPUT_DIR)
	@echo "$(COLOR_YELLOW)Linking $(TARGET) for $(PLATFORM_NAME)...$(COLOR_RESET)"
ifeq ($(USE_ZIG),1)
	$(ZIG) c++ $(CXXFLAGS) $(OBJS) -o $(TARGET) $(LDFLAGS)
else
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET) $(LDFLAGS)
endif

# Compile rules
$(OBJ)main$(OBJ_EXT): $(SRC)main.cpp $(HEADERS) | $(OBJ)
	@echo "$(COLOR_BLUE)Compiling main.cpp for $(PLATFORM_NAME)...$(COLOR_RESET)"
ifeq ($(USE_ZIG),1)
	$(ZIG) c++ $(CXXFLAGS) -c $< -o $@
else
	$(CXX) $(CXXFLAGS) -c $< -o $@
endif

$(OBJ)language_module$(OBJ_EXT): $(SRC)language_module.cpp $(SRC)language_module.h | $(OBJ)
	@echo "$(COLOR_BLUE)Compiling language_module.cpp...$(COLOR_RESET)"
ifeq ($(USE_ZIG),1)
	$(ZIG) c++ $(CXXFLAGS) -c $< -o $@
else
	$(CXX) $(CXXFLAGS) -c $< -o $@
endif

$(OBJ)consciousness_module$(OBJ_EXT): $(SRC)consciousness_module.cpp $(SRC)consciousness_module.h | $(OBJ)
	@echo "$(COLOR_BLUE)Compiling consciousness_module.cpp...$(COLOR_RESET)"
ifeq ($(USE_ZIG),1)
	$(ZIG) c++ $(CXXFLAGS) -c $< -o $@
else
	$(CXX) $(CXXFLAGS) -c $< -o $@
endif

$(OBJ)embodiment_module$(OBJ_EXT): $(SRC)embodiment_module.cpp $(SRC)embodiment_module.h | $(OBJ)
	@echo "$(COLOR_BLUE)Compiling embodiment_module.cpp...$(COLOR_RESET)"
ifeq ($(USE_ZIG),1)
	$(ZIG) c++ $(CXXFLAGS) -c $< -o $@
else
	$(CXX) $(CXXFLAGS) -c $< -o $@
endif

$(OBJ)metacognition_module$(OBJ_EXT): $(SRC)metacognition_module.cpp $(SRC)metacognition_module.h | $(OBJ)
	@echo "$(COLOR_BLUE)Compiling metacognition_module.cpp...$(COLOR_RESET)"
ifeq ($(USE_ZIG),1)
	$(ZIG) c++ $(CXXFLAGS) -c $< -o $@
else
	$(CXX) $(CXXFLAGS) -c $< -o $@
endif

$(OBJ)module_integration$(OBJ_EXT): $(SRC)module_integration.cpp $(SRC)module_integration.h | $(OBJ)
	@echo "$(COLOR_BLUE)Compiling module_integration.cpp...$(COLOR_RESET)"
ifeq ($(USE_ZIG),1)
	$(ZIG) c++ $(CXXFLAGS) -c $< -o $@
else
	$(CXX) $(CXXFLAGS) -c $< -o $@
endif

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

# Run the program (Linux only)
run: $(TARGET)
ifeq ($(TARGET_OS),linux)
	@echo "$(COLOR_GREEN)$(COLOR_BOLD)Starting Nexus...$(COLOR_RESET)"
	@./$(TARGET)
else
	@echo "$(COLOR_YELLOW)Cannot run Windows executable on Linux!$(COLOR_RESET)"
	@echo "$(COLOR_CYAN)Transfer $(TARGET) to Windows to run it.$(COLOR_RESET)"
endif

# Debug build
debug: CXXFLAGS += -g -O0 -DDEBUG
debug: clean all
	@echo "$(COLOR_GREEN)$(COLOR_BOLD)✓ Debug build complete$(COLOR_RESET)"

# Release build
release: CXXFLAGS += -DNDEBUG
release: clean all
	@echo "$(COLOR_GREEN)$(COLOR_BOLD)✓ Release build complete$(COLOR_RESET)"

# Build for both platforms
both: clean
	@echo "$(COLOR_MAGENTA)$(COLOR_BOLD)Building for both Linux and Windows...$(COLOR_RESET)"
	@$(MAKE) TARGET_OS=linux
	@$(MAKE) TARGET_OS=windows
	@echo "$(COLOR_GREEN)$(COLOR_BOLD)✓ Both builds complete!$(COLOR_RESET)"
	@ls -lh $(OUTPUT_DIR)

# Build only modules
modules: $(OBJ)language_module$(OBJ_EXT) \
         $(OBJ)consciousness_module$(OBJ_EXT) \
         $(OBJ)embodiment_module$(OBJ_EXT) \
         $(OBJ)metacognition_module$(OBJ_EXT) \
         $(OBJ)module_integration$(OBJ_EXT)
	@echo "$(COLOR_GREEN)✓ Consciousness modules compiled$(COLOR_RESET)"

# Install (Linux only)
install: release
ifeq ($(TARGET_OS),linux)
	@echo "$(COLOR_YELLOW)Installing to /usr/local/bin...$(COLOR_RESET)"
	@sudo cp $(TARGET) /usr/local/bin/Nexus
	@sudo chmod +x /usr/local/bin/Nexus
	@echo "$(COLOR_GREEN)✓ Installed! Run with: Nexus$(COLOR_RESET)"
else
	@echo "$(COLOR_YELLOW)Install target only available for Linux builds$(COLOR_RESET)"
endif

# Help target
help:
	@echo "$(COLOR_BOLD)Nexus Build System - Zig Cross-Compilation (No MinGW!)$(COLOR_RESET)"
	@echo ""
	@echo "$(COLOR_BOLD)QUICK START:$(COLOR_RESET)"
	@echo "  1. $(COLOR_GREEN)make install-zig$(COLOR_RESET)     - Install Zig compiler (one-time setup)"
	@echo "  2. $(COLOR_GREEN)make windows$(COLOR_RESET)         - Build Windows .exe from Linux"
	@echo ""
	@echo "$(COLOR_BOLD)BASIC USAGE:$(COLOR_RESET)"
	@echo "  $(COLOR_GREEN)make$(COLOR_RESET)                    - Build for Linux (native)"
	@echo "  $(COLOR_GREEN)make windows$(COLOR_RESET)            - Cross-compile for Windows"
	@echo "  $(COLOR_GREEN)make linux$(COLOR_RESET)              - Build for Linux"
	@echo "  $(COLOR_GREEN)make both$(COLOR_RESET)               - Build for both platforms"
	@echo ""
	@echo "$(COLOR_BOLD)OTHER TARGETS:$(COLOR_RESET)"
	@echo "  $(COLOR_GREEN)make run$(COLOR_RESET)                - Build and run (Linux only)"
	@echo "  $(COLOR_GREEN)make clean$(COLOR_RESET)              - Remove build artifacts"
	@echo "  $(COLOR_GREEN)make rebuild$(COLOR_RESET)            - Clean and rebuild"
	@echo "  $(COLOR_GREEN)make debug$(COLOR_RESET)              - Build with debug symbols"
	@echo "  $(COLOR_GREEN)make release$(COLOR_RESET)            - Build optimized release"
	@echo "  $(COLOR_GREEN)make modules$(COLOR_RESET)            - Build only consciousness modules"
	@echo ""
	@echo "$(COLOR_BOLD)WHY ZIG?$(COLOR_RESET)"
	@echo "  ✓ No MinGW needed - Zig bundles its own cross-compiler"
	@echo "  ✓ Single ~50MB download - installs in seconds"
	@echo "  ✓ No package manager or sudo required"
	@echo "  ✓ Works on any Linux distro"
	@echo "  ✓ Can target Windows, macOS, Linux from anywhere"
	@echo ""
	@echo "$(COLOR_BOLD)INSTALL ZIG:$(COLOR_RESET)"
	@echo "  $(COLOR_CYAN)Automatic:$(COLOR_RESET) make install-zig"
	@echo "  $(COLOR_CYAN)Manual:$(COLOR_RESET)    Download from https://ziglang.org/download/"
	@echo ""
	@echo "$(COLOR_BOLD)MODULE FILES:$(COLOR_RESET)"
	@echo "  • language_module.cpp      - N-grams, Markov chains"
	@echo "  • consciousness_module.cpp - IIT, Global Workspace"
	@echo "  • embodiment_module.cpp    - Grounding, Qualia"
	@echo "  • metacognition_module.cpp - Self-model, Dreams"
	@echo "  • module_integration.cpp   - Integration layer"
	@echo ""
	@echo "$(COLOR_BOLD)CURRENT CONFIG:$(COLOR_RESET)"
	@echo "  Target: $(TARGET_OS)"
	@echo "  Output: $(TARGET)"
	@echo ""