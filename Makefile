# dir config
BUILD_DIR=./build
DFS_DIR=./DFS
TARGET_DIR=./target
UTILS_DIR=./utils
# files
DFS_C_SRC=$(DFS_DIR)/dfs_c.c
DFS_C_OBJ=$(patsubst %.c,$(BUILD_DIR)/%.o,$(notdir $(DFS_C_SRC)))
DFS_C_BIN=$(BUILD_DIR)/dfs_c
DFS_RS_BIN=$(BUILD_DIR)/dfs_rs

LIBMAZE_SRC=$(UTILS_DIR)/maze.c
LIBMAZE_OBJ=$(BUILD_DIR)/libmaze.o
LIBMAZE_A=$(BUILD_DIR)/libmaze.a

LIBSTACK_SRC=$(UTILS_DIR)/stack.c
LIBSTACK_OBJ=$(BUILD_DIR)/libstack.o
LIBSTACK_A=$(BUILD_DIR)/libstack.a

# c config
AR = ar
CC = cc
CFLAGS = -Wall -O2 -I./libmaze -I./libstack
LDFLAGS = -L$(BUILD_DIR)
LDLIBS = -lmaze -lstack


.PHONY: build clean distclean libs

# c library
# libmaze
$(LIBMAZE_OBJ): $(LIBMAZE_SRC)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBMAZE_A): $(LIBMAZE_OBJ)
	$(AR) rcs $@ $^

# libstack
$(LIBSTACK_OBJ): $(LIBSTACK_SRC)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBSTACK_A): $(LIBSTACK_OBJ)
	$(AR) rcs $@ $^

libs: $(LIBMAZE_A) $(LIBSTACK_A)

# bin
$(BUILD_DIR)/%.o: $(DFS_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(DFS_C_BIN): $(DFS_C_OBJ) $(LIBMAZE_A) $(LIBSTACK_A)
	$(CC) -o $@ $(DFS_C_OBJ) $(LDFLAGS) $(LDLIBS)

$(DFS_RS_BIN):
	cargo build -p dfs_rs
	cp $(TARGET_DIR)/debug/dfs_rs $(DFS_RS_BIN)

build: $(BUILD_DIR)/dfs_c $(BUILD_DIR)/dfs_rs

distclean:
	rm $(BUILD_DIR)/*.o
	cargo clean
clean: distclean
	rm $(BUILD_DIR)/*
