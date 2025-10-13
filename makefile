# DIGITZ BUILD SYSTEM

TARGET := output/digitz
SRC := src/main.cpp
CXX := clang++
CXXFLAGS := -std=c++23 -O3 -pthread -rdynamic -march=native
LDFLAGS := -lncurses -lcurl 

DIALOG := $(shell command -v dialog 2>/dev/null)
HAS_BACKTITLE := $(shell dialog --help 2>&1 | grep -q backtitle && echo yes || echo no)
TERMUX := $(shell uname -o 2>/dev/null | grep -qi android && echo yes || echo no)

.PHONY: all build clean ensure-dialog

all: build

ensure-dialog:
ifndef DIALOG
	@echo "Installing 'dialog'..."
ifeq ($(TERMUX),yes)
	@pkg install -y dialog
else
	@sudo apt-get update -qq && sudo apt-get install -y dialog
endif
endif

build: ensure-dialog
	@mkdir -p output
	@export BT_OPT=""; export BT_VAL=""; \
	if [ "$(HAS_BACKTITLE)" = "yes" ]; then \
		export BT_OPT="--backtitle"; \
		export BT_VAL="DIGITZ BUILD SYSTEM"; \
	fi; \
	$(DIALOG) $$BT_OPT "$$BT_VAL" --title "Preparing" --infobox "⏳ Initializing..." 6 40 2>/dev/tty || true; \
	sleep 1; \
	( \
		echo 10; sleep 0.3; \
		echo 40; sleep 0.3; \
		if $(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS) 2>build.log; then \
			echo 90; \
		else \
			echo 50; \
		fi; \
		sleep 0.3; \
		echo 100; sleep 0.2; \
	) | $(DIALOG) $$BT_OPT "$$BT_VAL" --title "Building" --gauge "Compiling..." 8 50 0; \
	BUILD_STATUS=$$?; \
	if [ $$BUILD_STATUS -eq 0 ]; then \
		$(DIALOG) $$BT_OPT "$$BT_VAL" --title "✅ Complete" --msgbox "Build succeeded!\n\nBinary: $(TARGET)" 8 50 2>/dev/tty; \
	else \
		$(DIALOG) $$BT_OPT "$$BT_VAL" --title "❌ Failed" --textbox build.log 20 70 2>/dev/tty; \
	fi

clean:
	@rm -rf output build.log
	@echo "✨ Clean complete!"
