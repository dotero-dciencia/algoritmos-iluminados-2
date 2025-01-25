#include <iostream>
#include <vector>

// Devuelve 1 si hay camino desde inicio hasta fin y 0 si no lo hay
bool dfs(std::vector<std::vector<int>>& grafo, int inicio, int fin, std::vector<bool>& visitados) {

  visitados[inicio] = true;

  for (int i = 0; i < grafo[inicio].size(); i++) {
    if (!visitados[grafo[inicio][i]]) {
      if (grafo[inicio][i] == fin) return true;
      else return dfs(grafo, grafo[inicio][i], fin, visitados);
    }
  }

  return false;
}

int dfsTopo(std::vector<std::vector<int>>& grafo, std::vector<bool>& visitados, std::vector<int>& orden, int actual, int& c){

  visitados[actual] = true;
  for (int i = 0; i < grafo[actual].size(); i++){
    if (!visitados[grafo[actual][i]]){
      c = dfsTopo(grafo, visitados, orden, grafo[actual][i], c);
    }
  }

  orden[actual] = c;
  return --c;
}

std::vector<int> topoSort(std::vector<std::vector<int>>& grafo){

  std::vector<bool> visitados(grafo.size(), false);
  std::vector<int> orden(grafo.size(), 0);
  int c = grafo.size()-1;

  for (int i = 0; i < grafo.size(); i++){
    if (!visitados[i]){
      c = dfsTopo(grafo, visitados, orden, i, c);
    }
  }

  return orden;
}

// Componentes fuertemente conexos

int main() {
  
  std::vector<std::vector<int>> grafo = {
    {4},
    {1, 2, 2},
    {3},
    {1, 4},
    {}
  };

  std::vector<int> orden = topoSort(grafo);
  
  for (int i = 0; i < grafo.size(); i++)
    std::cout << i << " " << orden[i] << std::endl;

  return 0;
}