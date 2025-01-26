#include <vector>
#include <tuple>
#include <iostream>
#include <map>
#include <stack>

std::string bellmanFord(std::map<std::string, std::map<std::string, int>>& grafo, std::string inicio, std::string objetivo){
  
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

  std::string actual;
  std::map<std::string, int> vecinos;

  for (int i = 0; i < grafo.size() - 1; i++){
    for (const auto& nodo : grafo){
      for (const auto& vecino : nodo.second){
        if (distancia[nodo.first] + vecino.second < distancia[vecino.first]){
          distancia[vecino.first] = distancia[nodo.first] + vecino.second;
          anterior[vecino.first] = nodo.first;
        }
      }
    }
  }

  for (const auto& nodo : grafo){
      for (const auto& vecino : nodo.second){
        if (distancia[nodo.first] + vecino.second < distancia[vecino.first]){
          return("Ciclos");
        }
      }
    }

  // Sacar el camino

  std::stack<std::string> camino;
  std::string nodoCamino = objetivo;

  for (int i = 0; i < grafo.size(); i++){
    camino.push(nodoCamino);
    nodoCamino = anterior[nodoCamino];
    if (nodoCamino == "0") break;
    if (nodoCamino == "-1") return "NO_HAY_CAMINO";
  }
  
  std::string solucion = "";
  while(!camino.empty()){
    solucion += camino.top(); 
    camino.pop();
    solucion += " ";
  } 

  return solucion;
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

  std::cout << bellmanFord(grafo, "A", "D") << std::endl;

  return 0;
}
