#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>

int dfsTopo(std::vector<std::vector<int>>& grafo, std::vector<bool>& visitados, std::vector<int>& orden, int actual, int& c){

  // Lo marcamos como visitado
  visitados[actual] = true;

  // Por cada hijo, si no está visitado, llamamos a dfsTopo y el orden de este nodo será el que devuelva dicha función
  for (int i = 0; i < grafo[actual].size(); i++){
    if (!visitados[grafo[actual][i]]){
      c = dfsTopo(grafo, visitados, orden, grafo[actual][i], c);
    }
  }

  // Devolvemos el orden para el siguiente nodo
  orden[actual] = c;
  return --c;
}

std::vector<int> topoSort(std::vector<std::vector<int>>& grafo){

  // Definimos visitados, orden y c
  std::vector<bool> visitados(grafo.size(), false);
  std::vector<int> orden(grafo.size(), 0);
  int c = grafo.size()-1;

  // Por cada nodo del grafo en orden indiferente, si no está visitado llamamos a dfsTopo
  for (int i = 0; i < grafo.size(); i++){
    if (!visitados[i]){
      c = dfsTopo(grafo, visitados, orden, i, c);
    }
  }

  return orden;
}

void dfsKorasaju(std::vector<std::vector<int>>& grafo, int actual, std::vector<bool>& visitados, std::vector<int>& componente, int c) {

  visitados[actual] = true;
  componente[actual] = c;

  for (int i = 0; i < grafo[actual].size(); i++) {
    if (!visitados[grafo[actual][i]]) {
      componente[grafo[actual][i]] = c;
      dfsKorasaju(grafo, grafo[actual][i], visitados, componente, c);
    }
  }
}

int kosaraju(std::vector<std::vector<int>>& grafo){
  
  // Invertir las aristas del grafo
  std::vector<std::vector<int>> grafo_rev(grafo.size());
  for (int i = 0; i < grafo.size(); i++){
    for (int j = 0; j < grafo[i].size(); j++){
      grafo_rev[grafo[i][j]].push_back(i);
    }
  }

  // Calcular orden topológico inverso usando TOPOSORT
  std::vector<int> orden = topoSort(grafo_rev);

  // Ordenamos según orden topológico
  std::vector<std::tuple<int, int>> nodosOrdenados;
  
  for (int i = 0; i < orden.size(); i++){
    nodosOrdenados.push_back({orden[i], i});
  }
  
  std::sort(nodosOrdenados.begin(), nodosOrdenados.end());

  // DFS normal con una modificación: cada nodo que se llegue desde un nodo inicio pertenecerá al mismo componente
  std::vector<bool> visitadosDFS(grafo.size(), false);
  std::vector<int> componente(grafo.size());
  int c = 0;
  for (int i = 0; i < nodosOrdenados.size(); i++){
    if (!visitadosDFS[std::get<1>(nodosOrdenados[i])]){
      dfsKorasaju(grafo, std::get<1>(nodosOrdenados[i]), visitadosDFS, componente, c);
      c++;
    }
  }

  return c;
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



  std::cout << kosaraju(grafo) << std::endl;

  return 0;
}