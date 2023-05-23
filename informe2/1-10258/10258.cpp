#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct enviar {
  int problema;
  int tiempo;
  char resultado;
};

struct equipo {
  int id;
  int resueltos;
  int tiempo;
  bool envio_realizado;
  equipo() : resueltos(0), tiempo(0), envio_realizado(false) {}
};

bool ordenarEquipos(const equipo &a, const equipo &b) {
  return a.resueltos != b.resueltos               ? a.resueltos > b.resueltos
         : a.tiempo != b.tiempo                   ? a.tiempo < b.tiempo
         : a.envio_realizado != b.envio_realizado ? a.envio_realizado
                                                  : a.id < b.id;
}

void procesarDatos(equipo equipos[], vector<enviar> envios[],
                   int &concursante) {
  bool ya_resuelto = false;
  enviar tmp;

  while (cin.peek() != '\n' && cin.peek() != -1) {
    cin >> concursante >> tmp.problema >> tmp.tiempo >> tmp.resultado;
    cin.ignore(100, '\n');
    equipos[concursante].envio_realizado = true;

    ya_resuelto = false;
    for (const auto &envio : envios[concursante]) {
      if (envio.problema == tmp.problema && envio.resultado == 'C') {
        ya_resuelto = true;
        break;
      }
    }

    if (tmp.resultado == 'C' && !ya_resuelto) {
      equipos[concursante].tiempo += tmp.tiempo;
      equipos[concursante].resueltos++;
      for (const auto &envio : envios[concursante]) {
        if (envio.problema == tmp.problema && envio.resultado == 'I') {
          equipos[concursante].tiempo += 20;
        }
      }
    }

    envios[concursante].push_back(tmp);
  }
  cin.ignore(100, '\n');
}

void manejarCasos(int casos) {
  int concursante;
  cin.ignore(100, '\n');
  cin.ignore(100, '\n');

  while (casos--) {
    equipo equipos[101];
    vector<enviar> envios[101];

    for (int i = 0; i < 101; i++)
      equipos[i].id = i;

    procesarDatos(equipos, envios, concursante);
    sort(equipos, equipos + 101, ordenarEquipos);

    for (int i = 0; i < 101; i++) {
      if (equipos[i].envio_realizado == false)
        break;
      cout << equipos[i].id << " " << equipos[i].resueltos << " "
           << equipos[i].tiempo << endl;
    }

    if (casos)
      cout << endl;
  }
}

int main(void) {
  int casos;
  cin >> casos;
  manejarCasos(casos);
  return 0;
}
