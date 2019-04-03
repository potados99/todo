# Makefile boilerplate version 0.0.1 (20190204)

TARGET = todo

CC = gcc
CFLAGS = -Wall

SRC_DIR = src/
OBJ_DIR = build/
BIN_DIR = bin/

OUT_DIR = $(OBJ_DIR) $(BIN_DIR)

SOURCE = $(wildcard $(SRC_DIR)/*.c)
BASENAMES = $(notdir $(basename $(SOURCE)))
OBJECT = $(addsuffix .o, $(addprefix $(OBJ_DIR), $(BASENAMES)))

.PHONY: directories

all: directories $(TARGET)

$(TARGET): $(OBJECT)
	$(LINK.c) -o $@ $^
	mv $@ $(BIN_DIR) 

# Object file wildcard rule.
build/%.o: src/%.c
	$(COMPILE.c) $< -o $@

directories: $(OUT_DIR)

$(OUT_DIR):
	mkdir -p $(OUT_DIR)

clean:
	rm -rf $(OUT_DIR)
