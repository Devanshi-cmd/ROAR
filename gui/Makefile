# Separate Makefile to handle setup and run cleanly
# Works on Linux and macOS

.PHONY: setup build run clean

# Detect OS
UNAME := $(shell uname)

# Set executable path based on OS
ifeq ($(UNAME), Darwin)
    # macOS
    EXECUTABLE = build/ROAR_GUI.app/Contents/MacOS/ROAR_GUI
else
    # Linux
    EXECUTABLE = build/ROAR_GUI
endif

build:
	@rm -rf build #clean if exists (Fresh Build)

	@mkdir -p build
	@cd build && cmake ..

	@cd build && $(MAKE)

run: 
	@$(EXECUTABLE)

clean:
	@rm -rf build
	@echo "Build directory removed."