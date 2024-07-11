CC=gcc
CFLAGS=-Wall -Werror -Wextra
LDFLAGS=-lncurses
SOURCE1=pong.c
SOURCE2=pong_interactive.c
BUILD_DIR=../build

OBJECT1=$(BUILD_DIR)/$(patsubst %.c,%.o,$(SOURCE1))
OBJECT2=$(BUILD_DIR)/$(patsubst %.c,%.o,$(SOURCE2))
EXE1=$(BUILD_DIR)/pong
EXE2=$(BUILD_DIR)/pong_interactive

.PHONY: all clean rebuild

all: $(EXE1) $(EXE2)

$(EXE1): $(OBJECT1) | $(BUILD_DIR)
	$(CC) $(OBJECT1) -o $@ $(CFLAGS)

$(EXE2): $(OBJECT2) | $(BUILD_DIR)
	$(CC) $(OBJECT2) -o $@ $(CFLAGS) $(LDFLAGS)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)

rebuild: clean all
