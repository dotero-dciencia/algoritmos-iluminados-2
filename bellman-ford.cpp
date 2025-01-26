#include <vector>
#include <tuple>
#include <iostream>
#include <map>
#include <stack>
#include <sstream>

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
          return("NO_HAY_RUTA");
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
    if (nodoCamino == "-1") return "NO_HAY_RUTA";
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
  std::map<std::string, std::map<std::string, int>> grafo = {};

  std::string linea;
  std::getline(std::cin, linea);
  std::string inicio, fin;
  std::stringstream ss(linea);
  ss >> inicio >> fin;
  
  std::string nodoActual, nodoLlegada;
  int peso;

  std::map<std::string, int> vecinosActual;
  while (std::getline(std::cin, linea)){
    vecinosActual.clear();
    std::stringstream ss(linea);
    ss >> nodoActual;
    while (ss >> nodoLlegada >> peso){
      vecinosActual[nodoLlegada] = peso;
    }
    grafo[nodoActual] = vecinosActual;
  }  

  std::cout << bellmanFord(grafo, inicio, fin) << std::endl;

  return 0;
}
