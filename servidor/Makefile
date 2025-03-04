SRC_DIR   = src
BUILD_DIR = build
BIN_DIR   = bin

SOURCES = $(shell find $(SRC_DIR) -name '*.c')
HEADERS = $(shell find $(SRC_DIR) -name '*.h')
OBJS    = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SOURCES))
EXEC    = serv

CC           = gcc
CFLAGS       = -c -Wall
EXTRA_CFLAGS =
LDFLAGS      = -lm

ifdef DEBUG
  EXTRA_CFLAGS += -g -O0 -DDEBUG
endif

.PHONY: all clean

all : $(EXEC)

$(EXEC): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(OBJS) $(LDFLAGS) -o $(BIN_DIR)/$@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c Makefile $(HEADERS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(EXTRA_CFLAGS) $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)
