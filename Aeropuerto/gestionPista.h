#ifndef GESTIONPISTA_H_INCLUDED
#define GESTIONPISTA_H_INCLUDED

#include "listaAviones.h"

void gestionarPista (ST_TODASLASLISTAS * todasLasListas);

void aunarListas (ST_TODASLASLISTAS * todasLasListas, int * cliente, int * IDReservaPista, ST_LISTAAVIONES * avionesRegistrados, ST_LISTAAVIONES * listaAterrizaje, ST_COLA * colaDespegue);

#endif // GESTIONPISTA_H_INCLUDED
