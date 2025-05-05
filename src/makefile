#só para automatizar o processo de compilação
#não é de tudo necessário mas como estou tentando
#criar o habito de usar makefile, resolvi fazer um.

all: banqueiro

banqueiro: src/banqueiro.c
	gcc -pthread -o banqueiro src/main.c

clean:
	rm -f banqueiro