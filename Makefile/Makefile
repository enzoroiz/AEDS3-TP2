# Lista dos objetos
O_OBJS = maino.o funcoes.o
H_OBJS = mainh.o funcoes.o

# Nome do executável
MAIN_H = tp2h
MAIN_O = tp2o

# Argumentos para execução do programa
ARGS = input.txt output.txt

# Especifica o compilador
CC = gcc

# Especifica as opções do compilador, habilita aviso sobre erros
CFLAGS = -Wall -pg -g3

# Comando terminal para limpar sem confirmação
RM = rm -f

# Compilação do programa e passos das ligações de dependências
$(MAIN_H): $(H_OBJS)
	@$(CC) $(CFLAGS) $(H_OBJS) -lm -o $(MAIN_H)

$(MAIN_O): $(O_OBJS)
	@$(CC) $(CFLAGS) $(O_OBJS) -lm -o $(MAIN_O)

%.o: %.c %.h
	@$(CC) $(CFLAGS) $< -c 

clean:
	$(RM) $(MAIN_H) *.o
	$(RM) $(MAIN_O) *.o
	$(RM) gmon.out

run_h: $(MAIN_H)
	./$(MAIN_H) $(ARGS)

run_o: $(MAIN_O)
	./$(MAIN_O) $(ARGS) 
