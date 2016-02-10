# Lista dos objetos
OBJS = main.o CanaisTelefonia.o

# Nome do executável
MAIN = tp2h

# Argumentos para execução do programa
ARGS = input.txt output.txt

# Especifica o compilador
CC = gcc

# Especifica as opções do compilador, habilita aviso sobre erros
CFLAGS = -Wall -pg -g3

# Comando terminal para limpar sem confirmação
RM = rm -f

# Compilação do programa e passos das ligações de dependências
$(MAIN): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -lm -o $(MAIN)

%.o: %.c %.h
	@$(CC) $(CFLAGS) $< -c 

clean:
	$(RM) $(MAIN) *.o
	$(RM) gmon.out

run: $(MAIN)
	./$(MAIN) $(ARGS)
