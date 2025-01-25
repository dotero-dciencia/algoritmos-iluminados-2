#include <iostream>
#include <vector>
#include <queue>

int nComponentesConexos (std::vector<std::vector<int>>grafo){
  // Declaramos componenteActual que será el número de componentes, y vectores componente y visitados
  int componenteActual = 0;
  std::vector<int> componente(grafo.size(), 0);
  std::vector<bool> visitados(grafo.size(), 0);
  
  // Dos variables auxiliares: para el nodo actual y para los nodos hijos
  int actual;
  std::vector<int> hijos;

  // Por cada nodo del grafo en orden cualquiera
  for (int i = 0; i < grafo.size(); i++){

    // Si no está visitado
    if (!visitados[i]){

      // Creamos una cola y lo añadimos
      std::queue<int> cola;
      cola.push(i);

      // Mientras queden elementos en la cola 
      while(!cola.empty()){

        // Sacamos el elemento, lo marcamos como visitado y como parte de este componente
        actual = cola.front(); cola.pop();
        visitados[actual] = true;
        componente[actual] = componenteActual;

        // Por cada hijo que tenga, si no está visitado, se añade a la cola
        hijos = grafo[actual];
        for (int j = 0; j < hijos.size(); j++){
          if (!visitados[hijos[j]])
            cola.push(hijos[j]);
        }
      }

      // Cambiamos de componente
      componenteActual++;
    }
  }

  // Devolvemos el número de componentes totales
  return componenteActual;
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