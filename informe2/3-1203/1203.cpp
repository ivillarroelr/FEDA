#include <iostream>
#include <map>
#include <queue>
#include <string>
using namespace std;

/*
Declaración de autenticidad:
El siguiente código fue generado a partir
del análisis del código de Konstantin Saveljev(https://github.com/ksaveljev)
para el ejercicio 1203 en Online Judge (https://onlinejudge.org)
Se refactorizó el código, ordenándolo, extrayendo
lógica hacia métodos para mejorar comprensión y orden
y se comentó exhaustivamente.

Análisis asintótico:
Este código presenta una complejidad temporal de O(n log(n)) y una complejidad espacial de O(n).
La complejidad temporal se debe a la inserción y extracción en un mapa y una cola de prioridad,
estructuras que en cada operación requieren O(log(n)) pasos en el peor de los casos.
La complejidad espacial se origina a partir de la memoria necesaria para almacenar
las consultas en el mapa y la cola de prioridad. 
 */


// Clase para comparación personalizada para la cola de prioridad
class comparacion {
public:
  // Sobrecarga del operador ()
  bool operator()(const pair<int, int> &a, const pair<int, int> &b) {
    // Si los segundos elementos son iguales, compara los primeros
    // Los elementos con un primer valor menor tienen mayor prioridad
    if (a.second == b.second) {
      return a.first > b.first;
    }
    // Si los segundos elementos no son iguales, compara estos
    // Los elementos con un segundo valor menor tienen mayor prioridad
    else {
      return a.second > b.second;
    }
  }
};

int main(void) {
  int numConsulta, periodo, k;
  string comando;
  map<int, int> periodos;

  // Cola de prioridad con una función de comparación personalizada
  priority_queue<pair<int, int>, vector<pair<int, int>>, comparacion> cola;

  while (cin >> comando) {
    // Si el comando es "#", rompe el ciclo
    if (comando == "#") {
      break;
    }

    cin >> numConsulta >> periodo;

    // Guarda el periodo de la consulta en el mapa de periodos
    periodos[numConsulta] = periodo;

    // Añade la consulta a la cola de prioridad
    cola.push(make_pair(numConsulta, periodo));
  }

  // Lee la cantidad de consultas a procesar
  cin >> k;

  // Procesa 'k' consultas
  while (k--) {
    // Obtiene la consulta de mayor prioridad
    pair<int, int> temp = cola.top();
    cola.pop();

    cout << temp.first << endl;

    // Actualiza el periodo de la consulta y la vuelve a añadir a la cola de
    // prioridad
    temp.second += periodos[temp.first];
    cola.push(temp);
  }

  return 0;
}
