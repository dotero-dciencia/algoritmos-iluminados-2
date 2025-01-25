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

int nComponentesConexos (std::vector<std::vector<int>>grafo){
  int nComponentesConexos = 0;
  std::vector<int> componente(grafo.size(), 0);
  std::vector<bool> visitados(grafo.size(), 0), visitadosAux(grafo.size(), 0);
  
  int actual;

  for (int i = 0; i < grafo.size(); i++){
    if (!visitados[i]){
      nComponentesConexos++;
      std::queue<int> cola;
      visitadosAux.clear();
      cola.push(i);
      while(!cola.empty()){
        actual = cola.front(); cola.pop();
        visitadosAux[actual] = true;
        visitados[actual] = true;
        componente[actual] = nComponentesConexos;
        for (int j = 0; j < grafo[i].size(); j++){
          if (!visitadosAux[grafo[i][j]])
            cola.push(grafo[i][j]);
        }
      }
    }
  }

  return nComponentesConexos;
}

int main(){

  // Grafo como lista de adyacencia
  std::vector<std::vector<int>> grafo = {
    {1},
    {0},
    {},
    {}
  };

  std::cout << nComponentesConexos(grafo);
  return 0;
}