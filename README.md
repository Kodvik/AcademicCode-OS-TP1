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

```bash
./banqueiro 10 5 7
```

## 📚 Estrutura de Dados

* `disponiveis[]`: recursos atualmente disponíveis
* `maximo[][]`: demanda máxima de cada cliente
* `alocado[][]`: recursos atualmente alocados
* `necessario[][]`: recursos ainda necessários

## 👥 Threads

Cada cliente roda em sua própria thread, fazendo solicitações e liberando recursos aleatoriamente, respeitando o algoritmo de segurança de Banker.

## 📄 Entrega

Este repositório contém:

* Código-fonte (em `src/`)
* Makefile
* README explicativo

Você pode incluir o link deste repositório no relatório PDF a ser entregue.

```

---

Se quiser, posso gerar um `.zip` com todos os arquivos prontos ou ajudá-lo a criar o repositório público no GitHub com nome, descrição e push inicial. Deseja isso agora?
```
