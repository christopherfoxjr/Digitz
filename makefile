# DIGITZ BUILD SYSTEM - Windows Compatible

# Detect OS
ifeq ($(OS),Windows_NT)
	RM := del /Q
	RMDIR := rmdir /S /Q
	MKDIR := mkdir
	EXEC_EXT := .exe
	SHELL := cmd.exe
	# Windows Python paths - adjust to your Python installation
	PYTHON_INCLUDES := -IC:\Python312\include
	PYTHON_LIBS := -LC:\Python312\libs -lpython312
else
	RM := rm -f
	RMDIR := rm -rf
	MKDIR := mkdir -p
	EXEC_EXT :=
	PYTHON_INCLUDES := $(shell pkg-config --cflags python-3.12)
	PYTHON_LIBS := $(shell pkg-config --libs python-3.12)
endif

# Directories
TARGET := output/digitz$(EXEC_EXT)
SRC := src/
OBJ := obj/
OUTPUT_DIR := output/

# Compiler settings
CXX := clang++
CXXFLAGS := -std=c++23 -O3 -pthread $(PYTHON_INCLUDES)
LDFLAGS := -lncurses -lcurl -lm $(PYTHON_LIBS)

# Source files
MAIN_SRC := $(SRC)main.cpp
MODULE_SRCS := $(SRC)language_module.cpp \
			   $(SRC)consciousness_module.cpp \
			   $(SRC)metacognition_module.cpp \
			   $(SRC)python_runtime.cpp \
			   $(SRC)module_integration.cpp

SRCS := $(MAIN_SRC) $(MODULE_SRCS)
OBJS := $(patsubst $(SRC)%.cpp,$(OBJ)%.o,$(SRCS))

HEADERS := $(SRC)uac.h \
		   $(SRC)language_module.h \
		   $(SRC)consciousness_module.h \
		   $(SRC)embodiment_module.h \
		   $(SRC)metacognition_module.h \
		   $(SRC)module_integration.h

.DEFAULT_GOAL := all
.PHONY: all clean rebuild run debug release modules help

all: $(TARGET)
	@echo Build complete!

$(TARGET): $(OBJS) | $(OUTPUT_DIR)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET) $(LDFLAGS)

$(OBJ)%.o: $(SRC)%.cpp $(HEADERS) | $(OBJ)
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

$(OBJ):
	$(MKDIR) $(OBJ:%/=%)

$(OUTPUT_DIR):
	$(MKDIR) $(OUTPUT_DIR:%/=%)

clean:
	$(RMDIR) $(OBJ) $(OUTPUT_DIR)

rebuild: clean all

run: $(TARGET)
	$(TARGET)

help:
	@echo DIGITZ Build System - Available Targets:
	@echo make all     - Build the project
	@echo make run     - Build and run
	@echo make clean   - Remove build artifacts
	@echo make rebuild - Clean and rebuild
