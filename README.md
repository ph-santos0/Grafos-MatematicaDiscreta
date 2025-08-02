# Projeto de Grafos — Seminário de Matemática Discreta

Este repositório contém a implementação de um programa de manipulação de **grafos** desenvolvido como parte do **Seminário Avaliativo** da disciplina de **Matemática Discreta**, com foco prático e teórico em estruturas de grafos.

O objetivo do trabalho é permitir a exploração de conceitos de grafos por meio de uma aplicação computacional interativa, com suporte a importação, manipulação e execução de algoritmos clássicos sobre grafos representados por listas de adjacência.

---

## Funcionalidades Disponíveis

O programa oferece as seguintes operações sobre grafos:

1. **Importar Grafo** de um arquivo de texto  
2. **Criar Grafo Vazio** com número de vértices definido  
3. **Exibir Adjacências** de todos os vértices  
4. **Inserir Aresta** entre dois vértices com peso  
5. **Remover Aresta** existente  
6. **Consultar Adjacência** entre dois vértices  
7. **Consultar Primeiro Adjacente** de um vértice  
8. **Consultar Próximo Adjacente** após um determinado vértice  
9. **Consultar Lista Completa de Adjacentes** de um vértice  
10. **Exportar Grafo** para um arquivo de texto  
11. **Determinar o Menor Caminho** com o algoritmo de Dijkstra  
0. **Sair** do programa  

---

## Formato do Arquivo de Entrada

O grafo pode ser importado de um arquivo `.txt` com o seguinte formato:

1. **Linha 1**: Define se o grafo é direcionado ou não: `direcionado=sim` ou `direcionado=nao`  
2. **Linha 2**: Número de vértices  
3. **Linha 3**: Número de arestas  
4. **Linhas seguintes**: Lista de arestas no formato: `origem destino peso`

### Exemplo de entrada:

```text
direcionado=sim
18
20
0 1 15
0 11 10
1 2 20
1 11 12
2 3 5
3 4 10
3 12 25
4 5 8
4 13 15
5 6 7
6 7 12
7 8 5
8 9 10
9 10 20
10 15 18
11 12 15
12 13 10
13 14 12
14 15 14
15 16 10
