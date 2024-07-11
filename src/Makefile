CC=gcc
CFLAGS=-Wall -Werror -Wextra -std=c11
SOURCE1=pong.c
BUILD_DIR=../build

OBJECT1=$(BUILD_DIR)/$(patsubst %.c,%.o,$(SOURCE1))
EXE1=$(BUILD_DIR)/pong

.PHONY: all clean rebuild

all: $(EXE1)

$(EXE1): $(OBJECT1) | $(BUILD_DIR)
	$(CC) $^ -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(OBJECT1): $(SOURCE1) | $(BUILD_DIR)
	$(CC) -DQUEST1 $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) rm *.o

rebuild: clean all
