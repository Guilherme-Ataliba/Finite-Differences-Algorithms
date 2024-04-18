# Compilers
CC = gcc
PY = python

# Directories
INCLUDE = include
BUILD = build
SRC = source
BIN = scripts
FIG = figures
OUTPUT = output

# Files
GIF_FILE = figure.gif

# Dependencies
DEPS = $(INCLUDE)/auxilary.h
OBJS = $(BUILD)/algorithm.o $(BUILD)/auxilary.o

.PHONY: all
all: $(SRC)/algorithm

.PHONY: run
run: $(SRC)/algorithm $(SRC)/plot.py | $(SRC) $(BIN) $(OUTPUT)
	./$(BIN)/algorithm 
	PY $(SRC)/plot.py
	make clean

$(SRC)/algorithm: $(OBJS) | $(SRC) $(BIN)
	$(CC) $^ -o $(BIN)/$(@F)

$(BUILD)/%.o: $(SRC)/%.c $(DEPS) | $(SRC) $(BUILD)
	$(CC) -c $< -o $@
	

.PHONY: clean
clean: | $(BUILD)
	rm -f $(BUILD)/*.o
	

.PHONY: remove
remove: | $(BIN)
	rm -f $(BIN)/*.exe

.PHONY: graph
graph: $(FIG)/$(GIF_FILE) | $(FIG)
	start "$(FIG)/$(GIF_FILE)"

$(FIG)/$(GIF_FILE): | $(FIG)
	make run


# Directories Creation
INCLUDE = include
BUILD = build
SRC = source
BIN = scripts
FIG = figures
OUTPUT = output

$(INCLUDE):
	mkdir $@

$(BUILD):
	mkdir $@

$(SRC):
	mkdir $@

$(BIN):
	mkdir $@

$(FIG):
	mkdir $@

$(OUTPUT):
	mkdir $@