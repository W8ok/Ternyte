# Sources
SRCS = src/main.c \
			 src/utilities.c \
			 src/initialization.c \
			 src/simulation.c \
			 src/ui/panels.c \
			 src/ui/menus.c \
			 src/wires/draw_wires.c \
			 src/wires/wire_tools.c \
			 src/tools/tools.c \
			 src/gates/draw_binary.c \
			 src/gates/gate_tools.c

# Output directories
PROJECT_NAME = ternyte
OUT_DIR = executables
LINUX_DIR = $(OUT_DIR)/$(PROJECT_NAME)-linux
WINDOWS_DIR = $(OUT_DIR)/$(PROJECT_NAME)-windows
LINUX_ZIP = $(OUT_DIR)/$(PROJECT_NAME)-linux.tar.gz
WINDOWS_ZIP = $(OUT_DIR)/$(PROJECT_NAME)-windows.zip

# Binary names inside folders
LINUX_BIN = $(LINUX_DIR)/$(PROJECT_NAME).x86_64
WINDOWS_BIN = $(WINDOWS_DIR)/$(PROJECT_NAME).exe

# Linux Config
CC_LINUX = gcc
CFLAGS_LINUX = -std=c11 -Wall -Wextra -Isrc -O2
LDFLAGS_LINUX = -lraylib -lm -lpthread -ldl -s
OBJS_LINUX = $(SRCS:src/%.c=obj/linux/%.o)

# Windows Config
CC_WIN = x86_64-w64-mingw32-gcc
CFLAGS_WIN = -std=c11 -Wall -Wextra -Isrc -Iwinlibs/include
LDFLAGS_WIN = -Lwinlibs/lib -lraylib -lm -lpthread -lwinmm -lgdi32
OBJS_WIN = $(SRCS:src/%.c=obj/win/%.o)

# Simple Development Build
DEV_BIN = $(PROJECT_NAME)
DEV_OBJS = $(SRCS:src/%.c=obj/dev/%.o)

.DEFAULT_GOAL := $(DEV_BIN)

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
	@echo "Building Linux binary..."
	mkdir -p $(LINUX_DIR)
	$(CC_LINUX) $(CFLAGS_LINUX) -o $@ $(OBJS_LINUX) $(LDFLAGS_LINUX)

obj/linux/%.o: src/%.c
	mkdir -p $(@D)
	$(CC_LINUX) $(CFLAGS_LINUX) -c $< -o $@

$(LINUX_DIR): $(LINUX_BIN)
	@echo "Copying Linux libraries..."
	cp /usr/lib/libraylib.so.550 $(LINUX_DIR)/ 2>/dev/null || true
	cp /usr/lib/libgcc_s.so.1 $(LINUX_DIR)/ 2>/dev/null || true

$(LINUX_ZIP): $(LINUX_DIR)
	cd $(OUT_DIR) && tar -czf $(PROJECT_NAME)-linux.tar.gz $(PROJECT_NAME)-linux/
	@echo "Linux archive: $(LINUX_ZIP)"

# Windows Build Chain
$(WINDOWS_BIN): $(OBJS_WIN)
	@echo "Building Windows binary..."
	mkdir -p $(WINDOWS_DIR)
	$(CC_WIN) $(CFLAGS_WIN) -o $@ $(OBJS_WIN) $(LDFLAGS_WIN)

obj/win/%.o: src/%.c
	mkdir -p $(@D)
	$(CC_WIN) $(CFLAGS_WIN) -c $< -o $@

$(WINDOWS_DIR): $(WINDOWS_BIN)
	@echo "Copying Windows libraries..."
	cp winlibs/lib/raylib.dll $(WINDOWS_DIR)/ 2>/dev/null || echo "Note: Add raylib.dll manually"
	find /usr -name "libgcc_s_seh-1.dll" 2>/dev/null | head -1 | xargs -I {} cp {} $(WINDOWS_DIR)/ 2>/dev/null || true
	find /usr -name "libwinpthread-1.dll" 2>/dev/null | head -1 | xargs -I {} cp {} $(WINDOWS_DIR)/ 2>/dev/null || true

$(WINDOWS_ZIP): $(WINDOWS_DIR)
	cd $(OUT_DIR) && zip -rq $(PROJECT_NAME)-windows.zip $(PROJECT_NAME)-windows/
	@echo "Windows archive: $(WINDOWS_ZIP)"

# Utilities
run: $(DEV_BIN)
	./$(DEV_BIN)

clean:
	rm -rf $(OUT_DIR) obj/ $(DEV_BIN)

clean-linux:
	rm -rf $(LINUX_DIR) $(LINUX_ZIP) obj/linux/

clean-windows:
	rm -rf $(WINDOWS_DIR) $(WINDOWS_ZIP) obj/win/

clean-dev:
	rm -rf obj/dev/ $(DEV_BIN)

help:
	@echo "Available targets:"
	@echo "	make or make run	- Build/run development binary in root (.o in obj/dev/)"
	@echo "	make linux		- Build Linux folder + zip"
	@echo "	make windows		- Build Windows folder + zip"
	@echo "	make all		- Build both"
	@echo "	make clean		- Clean everything"
	@echo "	make clean-dev		- Clean only development build"
	@echo "	make clean-linux	- Clean Linux builds"
	@echo "	make clean-windows	- Clean Windows builds"

.PHONY: linux windows all run clean clean-dev clean-linux clean-windows help
