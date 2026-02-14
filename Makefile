# Sources — recursively include all .c files
SRCS := $(shell find src -name "*.c")

# Assets
ASSETS = assets/

# Output directories
PROJECT_NAME = ternyte
OUT_DIR = executables
LINUX_DIR = $(OUT_DIR)/$(PROJECT_NAME)-linux
LINUX_ZIP = $(OUT_DIR)/$(PROJECT_NAME)-linux.tar.gz
WINDOWS_DIR = $(OUT_DIR)/$(PROJECT_NAME)-windows
WINDOWS_ZIP = $(OUT_DIR)/$(PROJECT_NAME)-windows.zip

# Binary names inside folders
LINUX_BIN = $(LINUX_DIR)/$(PROJECT_NAME).x86_64
WINDOWS_BIN = $(WINDOWS_DIR)/$(PROJECT_NAME).exe

# Linux Config
CC_LINUX = gcc
CFLAGS_LINUX = -std=c11 -Wall -Wextra -Isrc -O2
LDFLAGS_LINUX = -lSDL3 -lGL -lm -lpthread -ldl -llua -s
OBJS_LINUX := $(patsubst src/%.c,obj/linux/%.o,$(SRCS))

# Windows Config
CC_WIN = x86_64-w64-mingw32-gcc
CFLAGS_WIN = -std=c11 -Wall -Wextra -Isrc -Iwinlibs/include
LDFLAGS_WIN = -Lwinlibs/lib -lSDL3 -lopengl32 -lm -lpthread -lwinmm -lgdi32 -llua
OBJS_WIN := $(patsubst src/%.c,obj/win/%.o,$(SRCS))

# Simple Development Build
DEV_BIN = $(PROJECT_NAME)
DEV_OBJS := $(patsubst src/%.c,obj/dev/%.o,$(SRCS))

.DEFAULT_GOAL := clean-make

linux: $(LINUX_ZIP)
windows: $(WINDOWS_ZIP)
all: linux windows

# Development Build
$(DEV_BIN): $(DEV_OBJS)
	$(CC_LINUX) $(CFLAGS_LINUX) -o $@ $(DEV_OBJS) $(LDFLAGS_LINUX)

obj/dev/%.o: src/%.c
	mkdir -p $(@D)
	$(CC_LINUX) $(CFLAGS_LINUX) -c $< -o $@

# Linux Build Chain
$(LINUX_BIN): $(OBJS_LINUX)
	mkdir -p $(LINUX_DIR)
	$(CC_LINUX) $(CFLAGS_LINUX) -o $@ $(OBJS_LINUX) $(LDFLAGS_LINUX)

obj/linux/%.o: src/%.c
	mkdir -p $(@D)
	$(CC_LINUX) $(CFLAGS_LINUX) -c $< -o $@

$(LINUX_DIR): $(LINUX_BIN)
	cp /usr/lib/libSDL3.so $(LINUX_DIR)/ 2>/dev/null || true
	cp /usr/lib/libgcc_s.so.1 $(LINUX_DIR)/ 2>/dev/null || true
	cp -r $(ASSETS) $(LINUX_DIR) 2>/dev/null || true

$(LINUX_ZIP): $(LINUX_DIR)
	cd $(OUT_DIR) && tar -czf $(PROJECT_NAME)-linux.tar.gz $(PROJECT_NAME)-linux/

# Windows Build Chain
$(WINDOWS_BIN): $(OBJS_WIN)
	mkdir -p $(WINDOWS_DIR)
	$(CC_WIN) $(CFLAGS_WIN) -o $@ $(OBJS_WIN) $(LDFLAGS_WIN)

obj/win/%.o: src/%.c
	mkdir -p $(@D)
	$(CC_WIN) $(CFLAGS_WIN) -c $< -o $@

$(WINDOWS_DIR): $(WINDOWS_BIN)
	cp winlibs/lib/SDL3.dll $(WINDOWS_DIR)/ 2>/dev/null || true
	find /usr -name "libgcc_s_seh-1.dll" 2>/dev/null | head -1 | xargs -I {} cp {} $(WINDOWS_DIR)/ 2>/dev/null || true
	find /usr -name "libwinpthread-1.dll" 2>/dev/null | head -1 | xargs -I {} cp {} $(WINDOWS_DIR)/ 2>/dev/null || true
	cp -r $(ASSETS) $(WINDOWS_DIR) 2>/dev/null || true

$(WINDOWS_ZIP): $(WINDOWS_DIR)
	cd $(OUT_DIR) && zip -rq $(PROJECT_NAME)-windows.zip $(PROJECT_NAME)-windows/

# Utilities
run: $(DEV_BIN)
	./$(DEV_BIN)

clean:
	rm -rf $(OUT_DIR) obj/ $(DEV_BIN)

clean-make:
	@make clean-dev > /dev/null 2>&1 || true
	@make $(DEV_BIN)

clean-linux:
	rm -rf $(LINUX_DIR) $(LINUX_ZIP) obj/linux/

clean-windows:
	rm -rf $(WINDOWS_DIR) $(WINDOWS_ZIP) obj/win/

clean-dev:
	rm -rf obj/dev/ $(DEV_BIN)

help:
	@echo "==================="
	@echo "$(shell echo $(PROJECT_NAME) | tr '[:lower:]' '[:upper:]') - Make Help"
	@echo "==================="
	@echo ""
	@echo "BUILD TARGETS:"
	@echo "  make 		Build development binary (default)"
	@echo "  make run	Build and run development binary"
	@echo "  make linux	Build Linux executable + archive"
	@echo "  make windows	Build Windows executable + archive"
	@echo "  make all	Build all available releases"
	@echo ""
	@echo "CLEAN TARGETS:"
	@echo "  make clean		Remove all build artifacts"
	@echo "  make clean-dev	Remove development build only"
	@echo "  make clean-linux	Remove Linux build only"
	@echo "  make clean-windows	Remove Windows build only"
	@echo ""
	@echo "OUTPUT:"
	@echo "  ./$(PROJECT_NAME)				- Development binary"
	@echo "  ./obj/				- Object files"
	@echo "  ./$(OUT_DIR)/$(PROJECT_NAME)-linux/		- Linux distribution"
	@echo "  ./$(OUT_DIR)/$(PROJECT_NAME)-windows/	- Windows distribution"

.PHONY: linux windows all run clean clean-dev clean-linux clean-windows help
