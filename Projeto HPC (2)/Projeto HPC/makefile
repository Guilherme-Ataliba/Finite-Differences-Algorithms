CC = gcc -fopenmp #Compilador para o C
OBJ = laplace.o 


laplace: $(OBJ) #necessário para compilar
	$(CC) $^ -o laplace 

%.o: %.c  #qualquer arquivo .o
	$(CC) -c $< -o $@ 

.PHONY: clean #apagar os arquivos.o
clean: 
	rm -f *.o 

