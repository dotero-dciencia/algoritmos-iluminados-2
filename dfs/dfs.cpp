#include <iostream>
#include <vector>

bool dfs(std::vector<std::vector<int>>& grafo, int inicio, int objetivo, std::vector<bool>& visitados) {

  // Marcamos el nodo actual como visitado
  visitados[inicio] = true;

  // Por cada hijo que tenga, si no está visitado, lo exploramos con DFS recursivo
  for (int i = 0; i < grafo[inicio].size(); i++) {
    if (!visitados[grafo[inicio][i]]) {
      return dfs(grafo, grafo[inicio][i], objetivo, visitados);
    }
  }

  // Devolvemos si está visitado o no el objetivo
  return visitados[objetivo];
  
}

int main() {
  
  std::vector<std::vector<int>> grafo = {
    {1},         // Nodo 0 tiene una arista hacia el nodo 1
    {2, 3},      // Nodo 1 tiene aristas hacia los nodos 2 y 3
    {0, 4},      // Nodo 2 tiene aristas hacia los nodos 0 y 4
    {4},         // Nodo 3 tiene una arista hacia el nodo 4
    {5},         // Nodo 4 tiene una arista hacia el nodo 5
    {3}          // Nodo 5 tiene una arista hacia el nodo 3
  };

  std::vector<bool> visitados(grafo.size(), false);

  std::cout << dfs(grafo, 5, 3, visitados) << std::endl;

  return 0;
}