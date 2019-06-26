#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string.h>
#include "gestionPista.h"
#define longBufferAyD 2
#define longID 9
#define tamanioBufferMensaje 100
#define esperaAterrizaje 15
#define esperaDespegue 15

/******************************************//**
*@fn  aunarListas
*
*@param c1 {ST_TODASLASLISTAS} * todasLasListas
*@param c2 {int} * cliente
*@param c3 {int} * IDReservaPista
*@param c4 {ST_LISTAAVIONES} * avionesRegistrados
*@param c5 {ST_LISTAAVIONES} * listaAterrizaje
*@param c6 {ST_COLA} * colaDespegue
********************************************/
void aunarListas (ST_TODASLASLISTAS * todasLasListas, int * cliente, int * IDReservaPista, ST_LISTAAVIONES * avionesRegistrados, ST_LISTAAVIONES * listaAterrizaje, ST_COLA * colaDespegue){
        todasLasListas->avionesRegistrados = avionesRegistrados;
        todasLasListas->listaAterrizaje = listaAterrizaje;
        todasLasListas->colaDespegue = colaDespegue;
        todasLasListas->cliente = *cliente;
        todasLasListas->reservapista = *IDReservaPista;
}
/******************************************//**
*@fn  despegueAvion
**suspende el proceso el tiempo especificado, simulando el tiempo
**de despegue del avion, una vez finalizado, imprime un mensaje
** indicando que el avion quedo en vuelo.
*@param c1 int ID
********************************************/
void despegueAvion (int ID){
        printf("\n \t\tAvion %i despegando ..↑↑↑..\n", ID);
        sleep(esperaDespegue);
        printf("\t\tAvion %i en vuelo ✈ \n", ID);
}

/******************************************//**
*@fn  aterrizajeAvion
**suspende el proceso 25 segundos, simulando el tiempo de
**aterrizaje del avion, una vez finalizado, imprime un mensaje
** indicando que el avion aterrizo.
*@param c1 int ID
********************************************/
void aterrizajeAvion (int ID){
        printf("\n \t\tAvion %i aterrizando ··↓↓↓··\n", ID);
        sleep(esperaAterrizaje);
        printf("\t\tAvion %i en hangar ✈ \n", ID);
}

/******************************************//**
*@fn gestionarPista
**Los aviones pueden solicitar pista para aterrizar.
**gestionara el avance de la cola de espera de los aviones que esten para despegar.
*@param c1 ST_TODASLASLISTAS * todasLasListas
********************************************/
void gestionarPista (ST_TODASLASLISTAS * todasLasListas){
    while (1){
        todasLasListas->pistaAsignada = 0;
        while (todasLasListas->listaAterrizaje!=NULL){
            ST_LISTAAVIONES * aux = todasLasListas->listaAterrizaje;
            todasLasListas->pistaAsignada = aux->avion->id;
            //printf("\n Se asignò la pista al avion ID %i\n", aux->avion->id);
            todasLasListas->listaAterrizaje = todasLasListas->listaAterrizaje->ste;
            enviarMensaje(aux->avion->cliente, 2);
            while (todasLasListas->reservapista != aux->avion->id){
                sleep (1);
            }
            ST_LISTAAVIONES * avion = buscarIDEnLista(aux->avion->id, &todasLasListas->avionesRegistrados);
            avion->avion->estado = 'a';
            enviarMensaje(aux->avion->cliente, 0);
            aterrizajeAvion(aux->avion->id);
            enviarMensaje(aux->avion->cliente, 4);
            avion->avion->estado = 'g';
            todasLasListas->reservapista = 0;
            free(aux);
        }
        if (todasLasListas->colaDespegue->cabecera!=NULL){
            ST_LISTAAVIONES *aux = todasLasListas->colaDespegue->cabecera;
            //printf("\n Se asignò la pista al avion ID %i\n", aux->avion->id);
            todasLasListas->pistaAsignada = aux->avion->id;
            enviarMensaje(aux->avion->cliente, 2);
            while (todasLasListas->reservapista != aux->avion->id){
                sleep (1);
            }
            ST_LISTAAVIONES * avion = buscarIDEnLista(aux->avion->id, &todasLasListas->avionesRegistrados);
            avion->avion->estado = 'd';
            enviarMensaje(aux->avion->cliente, 0);
            despegueAvion(aux->avion->id);
            enviarMensaje(aux->avion->cliente, 3);
            avion->avion->estado = 'v';
            todasLasListas->reservapista = 0;
            todasLasListas->colaDespegue->cabecera = todasLasListas->colaDespegue->cabecera->ste;
            free(aux);
        }
    }
}
