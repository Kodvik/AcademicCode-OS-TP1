# AcademicCode-OS-TP1

## Enunciado
[Trabalho Prático 1](./Trabalho%20Prático%201.pdf)

## Instruções de Configuração e Execução

### 1. Clonar o Repositório

```bash
git clone https://github.com/Kodvik/AcademicCode-OS-TP1.git
cd AcademicCode-OS-TP1
```

### 2. Compilar o Código
meio logico, mas o codigo vai exigir que tenha o `gcc` com suporte ao `pthread`, e como usei o makefile, é para me acostumar a fazer isso, utilize o comando `make` no diretório `src`:

```bash
cd src
make
```

Isso gerará o executável chamado `banqueiro` no mesmo diretório.

### 3. Executar o Programa
Após a compilação, o programa pode ser executado diretamente no terminal. Certifique-se de estar no diretório `src` e use o seguinte comando:

```bash
./banqueiro <recursos_tipo_1> <recursos_tipo_2> <recursos_tipo_3>
```

Por exemplo (igual do enunciado):

```bash
./banqueiro 10 5 7
```

Neste exemplo:
- `10` é o número de instâncias disponíveis do recurso tipo 0.
- `5` é o número de instâncias disponíveis do recurso tipo 1.
- `7` é o número de instâncias disponíveis do recurso tipo 2.

### 4. Limpar Arquivos Gerados
Para remover o executável gerado, utilize o comando:

```bash
make clean
```

## Estrutura de Dados

- `disponiveis[]`: Recursos atualmente disponíveis.
- `maximo[][]`: Demanda máxima de cada cliente.
- `alocado[][]`: Recursos atualmente alocados.
- `necessario[][]`: Recursos ainda necessários.

## Threads

Cada cliente roda em sua própria thread, fazendo solicitações e liberando recursos aleatoriamente, respeitando o algoritmo de segurança de Banker.
