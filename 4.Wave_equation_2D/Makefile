# Compilers
CC = gcc
PY = python

# Directories
INCLUDE = include
BUILD = build
SRC = source
BIN = scripts
FIG = figures

# Files
GIF_FILE = figure.gif

# Dependencies
DEPS = $(INCLUDE)/auxilary.h
OBJS = $(BUILD)/algorithm.o $(BUILD)/auxilary.o

.PHONY: all
all: $(SRC)/algorithm

.PHONY: run
run: $(SRC)/algorithm $(SRC)/plot.py
	./$(BIN)/algorithm 
	PY $(SRC)/plot.py
	make clean

$(SRC)/algorithm: $(OBJS)
	$(CC) $^ -o $(BIN)/$(@F)

$(BUILD)/%.o: $(SRC)/%.c $(DEPS)
	$(CC) -c $< -o $@
	

.PHONY: clean
clean: 
	rm -f $(BUILD)/*.o
	

.PHONY: remove
remove: 
	rm -f $(BIN)/*.exe

.PHONY: graph
graph: $(FIG)/$(GIF_FILE)
	start "$(FIG)/$(GIF_FILE)"

$(FIG)/$(GIF_FILE): 
	make run