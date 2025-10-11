# DIGITZ BUILD SYSTEM

TARGET := output/digitz
SRC := src/main.cpp
CXX := g++
CXXFLAGS := -std=c++17 -lncurses -lcurl

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
	@if [ "$(HAS_BACKTITLE)" = "yes" ]; then \
		BT_OPT="--backtitle" BT_VAL="DIGITZ BUILD SYSTEM"; \
	else \
		BT_OPT="" BT_VAL=""; \
	fi; \
	$(DIALOG) $$BT_OPT $$BT_VAL --title "Preparing" --infobox "⏳ Initializing..." 6 40 2>/dev/tty || true; \
	sleep 1; \
	{ \
		( \
			echo 10; sleep 0.3; \
			echo 40; sleep 0.3; \
			$(CXX) $(SRC) -o $(TARGET) $(CXXFLAGS) 2>build.log && echo 90 || echo 50; \
			sleep 0.3; \
			echo 100; sleep 0.2; \
		) | $(DIALOG) $$BT_OPT $$BT_VAL --title "Building" --gauge "Compiling..." 8 50 0; \
	}; \
	if [ $$? -eq 0 ]; then \
		$(DIALOG) $$BT_OPT $$BT_VAL --title "✅ Complete" --msgbox "Build succeeded!\n\nBinary: $(TARGET)" 8 50 2>/dev/tty; \
	else \
		$(DIALOG) $$BT_OPT $$BT_VAL --title "❌ Failed" --textbox build.log 20 70 2>/dev/tty; \
	fi

clean:
	@rm -rf output build.log
	@echo "✨ Clean complete!"