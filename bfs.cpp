#include <iostream>
#include <vector>
#include <queue>
#include <limits>

bool bfs(int inicio, int objetivo, std::vector<std::vector<int>>grafo){

  // Inicializamos todos los visitados a 0
  std::vector<bool> visitados(grafo.size());

  // Declaramos la cola y el primer elemento de la cola será el nodo de inicio
  std::queue<int> cola;
  cola.push(inicio);

  // Dos variables auxiliares: para el nodo actual y para los nodos hijos
  int actual;
  std::vector<int> hijos;

  // Mientras queden nodos por visitar en la cola
  while(!cola.empty()){

    // Definimos el nodo actual que estamos visitando, lo visitamos y quitamos de la cola. También nombramos sus hijos
    actual = cola.front(); visitados[actual] = 1; cola.pop();
    hijos = grafo[actual];

    // Por cada hijo que tenga, si no está visitado ya, se añade a la cola para visitarlo
    for (int i = 0; i < hijos.size(); i++){
      if (visitados[hijos[i]] == 0){
        cola.push(hijos[i]);
      }
    }
  }

  // Devolvemos si el objetivo ha sido visitado o no (0 o 1)
  return visitados[objetivo];
}

int bfsCaminoCorto(int inicio, int objetivo, std::vector<std::vector<int>>grafo){
  const int INF = std::numeric_limits<int>::max();

  // Inicializamos todos los visitados a 0
  std::vector<bool> visitados(grafo.size());
  std::vector<int> distancia(grafo.size(), INF);
  distancia[inicio] = 0;

  // Declaramos la cola y el primer elemento de la cola será el nodo de inicio
  std::queue<int> cola;
  cola.push(inicio);

  // Dos variables auxiliares: para el nodo actual y para los nodos hijos
  int actual;
  std::vector<int> hijos;

  // Mientras queden nodos por visitar en la cola
  while(!cola.empty()){

    // Definimos el nodo actual que estamos visitando, lo visitamos y quitamos de la cola. También nombramos sus hijos
    actual = cola.front(); visitados[actual] = 1; cola.pop();
    hijos = grafo[actual];

    // Por cada hijo que tenga, si no está visitado ya, se añade a la cola para visitarlo
    for (int i = 0; i < hijos.size(); i++){
      if (visitados[hijos[i]] == 0){
        cola.push(hijos[i]);
        distancia[hijos[i]] = distancia[actual]+1;
      }
    }
  }

  return distancia[objetivo];
}

int main(){

  // Grafo como lista de adyacencia
  std::vector<std::vector<int>> grafo = {
    {1, 3},
    {2},
    {3},
    {}
  };

  std::cout << bfsCaminoCorto(0, 2, grafo);
  return 0;
}