CC = gcc
OBJ = laplace.o utilidades.o
DEPS = utilidades.h

laplace: $(OBJ)
	$(CC) $^ -o laplace 

%.o: %.c $(DEPS)
	$(CC) -c $< -o $@ 

.PHONY: clean
clean:
	rm -f *.o