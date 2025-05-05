# AcademicCode-OS-TP1

```markdown
## Enunciado:
[Trabalho Prático 1](./Trabalho%20Prático%201.pdf)
```

## Instruções de Execução

```bash
./banqueiro <recursos_tipo_1> <recursos_tipo_2> <recursos_tipo_3>
```

Exemplo:
*do anunciado*
```bash
./banqueiro 10 5 7
```

## Estrutura de Dados

* `disponiveis[]`: recursos atualmente disponíveis
* `maximo[][]`: demanda máxima de cada cliente
* `alocado[][]`: recursos atualmente alocados
* `necessario[][]`: recursos ainda necessários

## Threads

Cada cliente roda em sua própria thread, fazendo solicitações e liberando recursos aleatoriamente, respeitando o algoritmo de segurança de Banker.
