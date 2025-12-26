BUILD_DEBUG   := cmake-build-debug
BUILD_RELEASE := cmake-build-release
GENERATOR     := Ninja
BINARY_DIR    := out
GENERATED_DIR := gen
BINARY_DEBUG  := $(BINARY_DIR)/debug/#PROJECT_NAME
BINARY_RELEASE:= $(BINARY_DIR)/release/#PROJECT_NAME

.PHONY: all debug release clean iwyu install test

all: debug release

debug:
	cmake -S . -B $(BUILD_DEBUG) -G $(GENERATOR) -DCMAKE_BUILD_TYPE=Debug
	cmake --build $(BUILD_DEBUG)

release:
	cmake -S . -B $(BUILD_RELEASE) -G $(GENERATOR) -DCMAKE_BUILD_TYPE=Release
	cmake --build $(BUILD_RELEASE)

clean:
	rm -rf $(BUILD_DEBUG) $(BUILD_RELEASE) $(BINARY_DIR) $(GENERATED_DIR)

# Adds/removes includes using include-what-you-use
iwyu: debug
	cmake --build $(BUILD_DEBUG) --target fix_includes_iwyu

test: debug
	cmake --build $(BUILD_DEBUG) --target #PROJECT_NAME_test

install: release
	sudo cp $(BINARY_RELEASE) /usr/local/bin/