# Compilers
CC = gcc
PY = python
CFLAGS = -lm -pg

# Directories
INCLUDE = include
BUILD = build
SRC = source
BIN = scripts
FIG = figures
OUTPUT = output
MULTI_MATRIX = $(OUTPUT)/multi_matrix  # Directory used to house each matrix output

# Files
GIF_FILE = figure.gif

# Dependencies
DEPS = $(INCLUDE)/auxilary.h
OBJS = $(BUILD)/algorithm.o $(BUILD)/auxilary.o

.PHONY: all
all: $(SRC)/algorithm

.PHONY: run
run: $(SRC)/algorithm $(SRC)/plot.py | $(SRC) $(BIN) $(OUTPUT) $(MULTI_MATRIX)
	./$(BIN)/algorithm 
	PY $(SRC)/plot.py
	make clean

$(SRC)/algorithm: $(OBJS) | $(SRC) $(BIN)
	$(CC) $(CFLAGS) $^ -o $(BIN)/$(@F)

$(BUILD)/%.o: $(SRC)/%.c $(DEPS) | $(SRC) $(BUILD)
	$(CC) $(CFLAGS) -c $< -o $@
	

.PHONY: clean
clean: | $(BUILD)
	rm -f $(BUILD)/*.o
	

.PHONY: remove
remove: | $(BIN)
	rm -f $(BIN)/*.exe
	rm -f $(OUTPUT)/Execution_time.txt
	rm -f $(OUTPUT)/multi_matrix/*

.PHONY: graph
graph: $(FIG)/$(GIF_FILE) | $(FIG)
	start "$(FIG)/$(GIF_FILE)"

$(FIG)/$(GIF_FILE): | $(FIG)
	make run


# Directories Creation
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

$(MULTI_MATRIX): 
	mkdir $@