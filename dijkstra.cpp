#include <vector>
#include <tuple>
#include <queue>
#include <iostream>
#include <map>
#include <algorithm>

std::string dijkstra(std::map<std::string, std::map<std::string, int>>& grafo, std::string inicio, std::string objetivo){
  
  std::map<std::string, bool> visitados;
  std::map<std::string, int> distancia;
  std::map<std::string, std::string> anterior;

  for (const auto& nodo : grafo) {
    visitados[nodo.first] = false;
    distancia[nodo.first] = 99999;
    anterior[nodo.first] = "-1";
  }

  distancia[inicio] = 0;
  anterior[inicio] = "0";
  std::priority_queue<
        std::tuple<int, std::string>, 
        std::vector<std::tuple<int, std::string>>, 
        std::greater<std::tuple<int, std::string>>
    > cola;
  cola.push({0, inicio});

  std::string actual;
  std::map<std::string, int> vecinos;
  while(!cola.empty()){
    actual = std::get<1>(cola.top()); cola.pop(); visitados[actual] = true;
    vecinos = grafo[actual];

    for (const auto& nodo : vecinos){
      if (distancia[actual] + nodo.second < distancia[nodo.first]){
        distancia[nodo.first] = distancia[actual] + nodo.second;
        anterior[nodo.first] = actual;
      }
      if (!visitados[nodo.first]){
        cola.push({distancia[nodo.first], nodo.first});
      }
    }
  }

  // Sacar el camino

  std::string camino = "", nodoCamino = objetivo;
  camino += objetivo;

  for (int i = 0; i < grafo.size(); i++){
    nodoCamino = anterior[nodoCamino];
    if (nodoCamino == "0") break; 
    camino += nodoCamino;
  }

  std::reverse(camino.begin(), camino.end());
  return camino;
}

int main() {
  // std::vector<std::vector<int>> grafo = {
  //       {0, 5, 10, 0, 0, 0},  // Nodo 0
  //       {5, 0, 0, 7, 3, 0},   // Nodo 1
  //       {10, 0, 0, 2, 0, 8},  // Nodo 2
  //       {0, 7, 2, 0, 6, 0},   // Nodo 3
  //       {0, 3, 0, 6, 0, 4},   // Nodo 4
  //       {0, 0, 8, 0, 4, 0}    // Nodo 5
  //   };

  std::map<std::string, std::map<std::string, int>> grafo = {
    {"A", {{"B", 3}, {"C", 2}}},
    {"B", {{"A", 3}, {"C", 1}, {"D", 4}}},
    {"C", {{"A", 2}, {"B", 1}, {"D", 5}}},
    {"D", {{"B", 4}, {"C", 5}}}
  };

  std::cout << dijkstra(grafo, "A", "D") << std::endl;

  return 0;
}
