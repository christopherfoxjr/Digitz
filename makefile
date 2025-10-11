# DIGITZ BUILD SYSTEM

TARGET = output/digitz
SRC = src/main.cpp
CXX = g++
CXXFLAGS = -std=c++17 -lncurses -lcurl
DIALOG = $(shell command -v dialog 2>/dev/null)

.PHONY: all clean build ensure-dialog

all: build

ensure-dialog:
ifndef DIALOG
	@echo "Installing 'dialog'..."
	@sudo apt-get update -qq && sudo apt-get install -y dialog
endif

build: ensure-dialog
	@mkdir -p output
	@$(DIALOG) --backtitle "DIGITZ BUILD SYSTEM" --title "Preparing" \
	           --infobox "⏳ Initializing..." 6 40
	@sleep 1
	@{ \
		( \
			echo 10; sleep 0.4; \
			echo 30; sleep 0.4; \
			$(CXX) $(SRC) -o $(TARGET) $(CXXFLAGS) 2> build.log && echo 90 || echo 50; \
			sleep 0.3; \
			echo 100; sleep 0.2; \
		) | $(DIALOG) --backtitle "DIGITZ BUILD SYSTEM" \
		              --title "Building" \
		              --gauge "Compiling $(SRC)..." 8 50 0; \
	}
	@if [ $$? -eq 0 ]; then \
		$(DIALOG) --backtitle "DIGITZ BUILD SYSTEM" --title "✅ Complete" \
		          --msgbox "Build successful!\n\nBinary: $(TARGET)" 8 50; \
	else \
		$(DIALOG) --backtitle "DIGITZ BUILD SYSTEM" --title "❌ Failed" \
		          --textbox build.log 20 70; \
	fi

clean:
	@rm -rf output build.log
	@echo "Clean complete."
