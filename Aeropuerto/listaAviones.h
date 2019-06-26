#ifndef LISTAAVIONES_H_INCLUDED
#define LISTAAVIONES_H_INCLUDED

#include "aviones.h"

/******************************************//**
** TAD: listaAviones
**En este TAD gestionaremos las listas de los aviones

**CONJUNTOS DE DATOS:
**----------Estructuras-----------:
*ST_LISTAAVIONES, ST_AVION, ST_COLA
**----------Variables-------------:
*ID, avion
**----------Punteros--------------:
*cliente, cabecera, avion, cola, listaAterrizar, colaDespegar, IDReservaPista, todasLasListas.

**OPERACIONES:
*1--void crearLista (ST_LISTAAVIONES**cabecera)
*2--ST_LISTAAVIONES * crearNodo (ST_AVION * avion)
*3--void crearCola(ST_COLA * cola)
*4--void agregarACola (ST_COLA * cola, ST_AVION * avion)
*5--void insertarOrdenado (ST_LISTAAVIONES ** cabecera, ST_AVION avion)
*6--void mostrarLista (ST_LISTAAVIONES**cabecera)
*7--ST_LISTAAVIONES * buscarIDEnLista (int ID, ST_LISTAAVIONES ** cabecera)
*8--void ordenarPorCombustible (ST_LISTAAVIONES ** cabecera, ST_AVION avion)
*9--void solicitarPista (ST_LISTAAVIONES ** listaAterrizar, ST_COLA * colaDespegar, ST_AVION * avion)
*10--int parsearMensaje (char * bufferMensaje, ST_AVION * avion)
*11--void caracterizarAvion (ST_AVION * avion)
*12--void recibirMensajeEnHilo (ST_TODASLASLISTAS * todasLasListas)
*******************************************/



/*****************************//**
*@struct ST_LISTAAVIONES
*@struct struct listaAviones * ste
**Estructura para listar a los aviones
********************************/
typedef struct listaAviones {
    ST_AVION * avion;
    struct listaAviones * ste;
}ST_LISTAAVIONES;


/*****************************//**
*@struct ST_COLA
**estructura para una cola
********************************/

typedef struct {
    ST_LISTAAVIONES *cabecera;
    ST_LISTAAVIONES *fin;
}ST_COLA;

/*****************************//**
*@struct ST_TODASLASLISTAS
**Esta estructura reune las listas de los
aviones registrados, la lista de los aviones que
estan por Aterrizar, la cola de los aviones que estan
por despegar.
********************************/
typedef struct {
    ST_LISTAAVIONES * avionesRegistrados;
    ST_LISTAAVIONES * listaAterrizaje;
    ST_COLA * colaDespegue;
    int cliente;
    int reservapista;
    int pistaAsignada;
    int avionEliminado;
} ST_TODASLASLISTAS;

void crearCola(ST_COLA * cola);

void agregarACola (ST_COLA * cola, ST_AVION * avion);

void crearLista (ST_LISTAAVIONES**cabecera);

void insertarEnLista (ST_LISTAAVIONES ** cabecera, ST_AVION * avion);

void mostrarLista (ST_LISTAAVIONES**cabecera);

ST_LISTAAVIONES * buscarIDEnLista (int ID, ST_LISTAAVIONES ** cabecera);

void ordenarPorCombustible (ST_LISTAAVIONES ** cabecera, ST_AVION * avion);

void solicitarPista (ST_LISTAAVIONES ** listaAterrizar, ST_COLA * colaDespegar, ST_AVION * avion);

void recibirMensajeEnHilo (ST_TODASLASLISTAS * todasLasListas);

void eliminarAvion (ST_TODASLASLISTAS * todasLasListas);

#endif // LISTAAVIONES_H_INCLUDED
