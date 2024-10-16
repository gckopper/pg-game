# Trabalho de processamento gráfico - GA - 2024/2

Alunos: Gabriel Kopper e Lucas Sauer

## Compilação

Primeiro clone a branch entrega deste repositório
```
git clone https://github.com/gckopper/pg-game/tree/entrega
cd pg-game
```

Sincronize os submodulos do git para baixar as dependencias

```
git submodule update --init --recursive extern/
```

Compilando o projeto

```
cmake -B build

cmake --build build --target install
```

Rodando o programa

```
cd install
./main.exe
```
