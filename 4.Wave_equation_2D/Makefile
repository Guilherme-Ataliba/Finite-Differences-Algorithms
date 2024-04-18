# Compilers
CC = gcc
PY = python

# Directories
INCLUDE = include
BUILD = build
SRC = src
BIN = bin

# Dependencies
DEPS = $(INCLUDE)/auxilary.h
OBJS = $(BUILD)/algorithm.o $(BUILD)/auxilary.o

.PHONY: all
all: $(SRC)/algorithm

.PHONY: run
run: $(SRC)/algorithm src/plot.py
	./bin/algorithm 
	PY src/plot.py
	make clean

$(SRC)/algorithm: $(OBJS)
	$(CC) $^ -o bin/$(@F)

$(BUILD)/%.o: $(SRC)/%.c $(DEPS)
	$(CC) -c $< -o $@
	

.PHONY: clean
clean: 
	rm -f $(BUILD)/*.o
	

.PHONY: remove
remove: 
	rm -f bin/*.exe

.PHONY: graph
graph: images/ani_test.gif
	start "images/ani_test.gif"

images/ani_test.gif: 
	make run