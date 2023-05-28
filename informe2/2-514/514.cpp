// Bibliotecas estándar que necesitamos
#include <iostream>
#include <stack>

using namespace std;

/*
Declaración de autenticidad:
El siguiente código fue generado a partir
del análisis del código de Konstantin Saveljev(https://github.com/ksaveljev)
para el ejercicio 514 en Online Judge (https://onlinejudge.org)
Se refactorizó el código, ordenándolo, extrayendo
lógica hacia métodos para mejorar comprensión y orden
y se comentó exhaustivamente.

Análisis asintótico:
Temporal: El peor de los casos es O(n) al tener la parte más pesada del análisis en
la función verificaSecuencia() la cual contiene un ciclo for que se
ejecuta 'n' veces, donde 'n' es el número de vagones en el tren.

Espacial: Se utiliza una matriz de tamaño 1010 y una pila. En el peor de los casos,
todos los 'n' elementos se agregan a la pila por lo tanto es O(n).
*/

// Limpia la pila que se pasa por referencia.
void limpiaPila(stack<int> &s) {
  // Se remueve el elemento superior mientras la pila no esté vacía.
  while (!s.empty())
    s.pop();
}

// Esta función maneja la lógica principal para verificar la secuencia de los
// vagones tren[]: array de los números de vagones n:  número de vagones actual:
// número de vagón buscado ok: verifica si la secuencia es correcta s: pila para
// manejar la secuencia
void verificaSecuencia(int tren[], int n, int &actual, bool &ok,
                       stack<int> &s) {
  // Se recorre el array de los vagones
  for (int i = 0; i < n; i++) {
    // Se agrega a la pila si el vagon actual es mayor al que se busca.
    while (tren[i] > actual) {
      s.push(actual++);
    }

    // Y si es el que estamos buscando seguimos con el siguiente.
    if (tren[i] == actual) {
      actual++;
      continue;
    }

    // Si la pila no está vacía y el vagón en la cima de la pila es el que
    // estamos buscando, lo sacamos de la pila
    if (!s.empty() && s.top() == tren[i]) {
      s.pop();
      continue;
    }

    // Si ninguno de los casos se cumple, la secuencia no es válida y rompemos
    // el ciclo
    ok = false;
    break;
  }
}

int main() {
  int n;          // N° de vagones
  int tren[1010]; // Array de los vagones
  int actual;     // N° del vagón buscado
  bool ok;        // Para verificar si la secuencia es correcta
  stack<int> s;   // Pila para manejar la secuencia

  // Mientras el número de vagones no sea 0
  while (cin >> n && n != 0) {
    // Mientras el primer vagón no sea 0
    while (cin >> tren[0] && tren[0] != 0) {
      // Se leen los números de los demás vagones
      for (int i = 1; i < n; i++)
        cin >> tren[i];

      limpiaPila(s);
      // Comienza la búsqueda desde el vagón n° 1
      actual = 1;
      // Suponemos que la secuencia es válida hasta que se demuestre lo
      // contrario
      ok = true;

      // Verificamos la secuencia de los vagones
      verificaSecuencia(tren, n, actual, ok, s);

      if (ok) {
        cout << "Yes" << endl;
      } else {
        cout << "No" << endl;
      }
    }
    cout << endl;
  }
  return 0;
}
