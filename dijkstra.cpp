#include <vector>
#include <tuple>
#include <queue>
#include <iostream>

void dijkstra(std::vector<std::vector<int>>& grafo, std::vector<int>& distancia, int inicio){
  
  std::vector<bool> visitados(grafo.size(), false);
  distancia[inicio] = 0;
  std::priority_queue<std::tuple<int, int>> cola;
  cola.push({0, inicio});

  int actual;
  std::vector<int> vecinos;
  while(!cola.empty()){
    actual = std::get<1>(cola.top()); cola.pop(); visitados[actual] = true;
    vecinos = grafo[actual];

    for (int i = 0; i < vecinos.size(); i++){
      if (vecinos[i] != 0){
        if (distancia[actual] + grafo[actual][i] < distancia[i]){
          distancia[i] = distancia[actual] + grafo[actual][i];
        }
        if (!visitados[i]){
          cola.push({distancia[i], i});
        }
      }
      
    }
  }
}

int main() {
  std::vector<std::vector<int>> grafo = {
        {0, 5, 10, 0, 0, 0},  // Nodo 0
        {5, 0, 0, 7, 3, 0},   // Nodo 1
        {10, 0, 0, 2, 0, 8},  // Nodo 2
        {0, 7, 2, 0, 6, 0},   // Nodo 3
        {0, 3, 0, 6, 0, 4},   // Nodo 4
        {0, 0, 8, 0, 4, 0}    // Nodo 5
    };
  
  std::vector<int> distancia(grafo.size(), 99999);
  dijkstra(grafo, distancia, 0);

  std::cout << distancia[3] << std::endl;

  return 0;
}
