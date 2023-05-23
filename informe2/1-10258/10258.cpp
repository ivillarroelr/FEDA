// Incluimos las bibliotecas necesarias
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

/*
Declaración de autenticidad:
El siguiente código fue generado a partir
del análisis del código de Konstantin Saveljev(https://github.com/ksaveljev)
para el ejercicio 10258 en Online Judge (https://onlinejudge.org)
Se refactorizó el código, ordenándolo, extrayendo
lógica hacia métodos para mejorar comprensión y orden
y se comentó exhaustivamente.
 */

// Estructura que para el envío de un problema
struct enviar {
  int problema; // ID del problema
  int tiempo; // Tiempo transcurrido
  char resultado; // Resultado del problema (C = Correcto, I = Incorrecto)
};

// Estructura para un equipo
struct equipo {
  int id; // ID del equipo
  int resueltos; // Problemas resueltos
  int tiempo; // Tiempo acumulado
  bool envio_realizado; // El equipo ha realizado al menos 1 envío
  equipo() : resueltos(0), tiempo(0), envio_realizado(false) {}
};

// Función para ordenar los equipos. Se utiliza en la función sort() de la biblioteca algorithm
bool ordenarEquipos(const equipo &a, const equipo &b) {
  // Si el número de problemas resueltos es diferente, se ordena de mayor a menor
  // Si son iguales, se verifica el tiempo total, ordenándolo de menor a mayor
  // Si el tiempo también es igual, se verifica si han realizado envíos, dándole preferencia a quienes sí lo han hecho
  // Finalmente, si todas las anteriores son iguales, se ordena por ID de menor a mayor
  return a.resueltos != b.resueltos ? a.resueltos > b.resueltos :
         a.tiempo != b.tiempo ? a.tiempo < b.tiempo :
         a.envio_realizado != b.envio_realizado ? a.envio_realizado :
         a.id < b.id;
}

// Procesa los datos de entrada
void procesarDatos(equipo equipos[], vector<enviar> envios[], int &concursante) {
  bool ya_resuelto = false; // Variable para verificar si un problema ya fue resuelto
  enviar tmp; // Variable temporal para guardar el envío actual

  // Mientras hayan líneas para leer
  while (cin.peek() != '\n' && cin.peek() != -1) {
    // Lee los datos de entrada del envío
    cin >> concursante >> tmp.problema >> tmp.tiempo >> tmp.resultado;
    cin.ignore(100, '\n');
    equipos[concursante].envio_realizado = true; // Este equipo ha realizado al menos un envío

    // Verifica si el problema ya fue resuelto
    ya_resuelto = false;
    for (const auto &envio : envios[concursante]) {
        if (envio.problema == tmp.problema && envio.resultado == 'C') {
            ya_resuelto = true;
            break;
        }
    }

    // Si el envío es correcto y no fue resuelto anteriormente
    if (tmp.resultado == 'C' && !ya_resuelto) {
        // Aumenta el tiempo total del equipo con el tiempo de este envío
        equipos[concursante].tiempo += tmp.tiempo;
        equipos[concursante].resueltos++; // Incrementa el contador de problemas resueltos
        // Suma 20 minutos por cada envío incorrecto previo al mismo problema
        for (const auto &envio : envios[concursante]) {
          if (envio.problema == tmp.problema && envio.resultado == 'I') {
            equipos[concursante].tiempo += 20;
          }
        }
    }

    // Agrega el envío a la lista de envíos del equipo
    envios[concursante].push_back(tmp);
  }
  cin.ignore(100, '\n');
}

// Función para manejar los casos de prueba
void manejarCasos(int casos) {
  int concursante; // Variable para guardar el ID del concursante actual
  cin.ignore(100, '\n');
  cin.ignore(100, '\n');

  // Mientras hayan casos de prueba
  while (casos--) {
    equipo equipos[101]; // Crea un array de equipos
    vector<enviar> envios[101]; // Crea un array de listas de envíos

    // Inicializa los ID de los equipos
    for (int i = 0; i < 101; i++)
      equipos[i].id = i;

    // Procesa los datos de entrada
    procesarDatos(equipos, envios, concursante);
    // Ordena los equipos según las reglas declaradas
    sort(equipos, equipos + 101, ordenarEquipos);

    // Muestra la información de los equipos que hayan realizado envíos
    for (int i = 0; i < 101; i++) {
      if (equipos[i].envio_realizado == false) // Si el equipo no ha realizado envíos, se sale del ciclo
        break;
      cout << equipos[i].id << " " << equipos[i].resueltos << " " << equipos[i].tiempo << endl; // Display de la información del equipo
    }

    // Si aún hay casos de prueba, se imprime una línea en blanco
    if (casos)
      cout << endl;
  }
}

int main(void) {
  int casos; // Número de casos de prueba
  cin >> casos;
  manejarCasos(casos); // Manejar los casos de prueba (llamada principal)
  return 0;
}
