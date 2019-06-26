#include "consola.h"
#include "avion.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#define tamanioBufferMensaje 100

/******************************************//**
*@fn conectar
**se realiza coneccion del avión con el aeropuerto
*@param int cliente
*@param struct sockaddr_in direccionServidor
*@return 1
********************************************/
int conectar (int cliente, struct sockaddr_in direccionServidor){
        if (connect(cliente, (void*) &direccionServidor, sizeof(direccionServidor)) != 0) {
                perror("No se pudo conectar");
                return 1;
            }
}

void mostrarOpcionesConsola(){
    printf("\n[1] - Registrar avion");
    printf("\n[2] - Solicitar pista");
    printf("\n[3] - Despegar");
    printf("\n[4] - Aterrizar");
    printf("\n[5] - Mostrar estado");
    printf("\n[6] - Salir\n");
}


/*******************************************//**
*@fn abrirConsola
**abre un menú de opciones, muestra las característica del avión actual
*@param struct sockaddr_in direccionServidor
*@param int cliente
*@param char * IP
*@param char*puerto
*@param ST_AVION *avion
*@param int * pistaAsignada
********************************************/
void abrirConsola(struct sockaddr_in direccionServidor, int cliente, char * IP, char*puerto, ST_AVION *avion){
    printf("\n Bienvenido al sistema de control del avion\n");
    mostrarEstadoAvion(avion);
    mostrarOpcionesConsola();
    int N=0;
    scanf("%d",&N);
    switch (N){
        case 1:
        system("clear");
        conectar(cliente, direccionServidor);
        registracion(cliente, IP, puerto, avion);
        abrirConsola(direccionServidor, cliente, IP, puerto, avion);
        break;
        case 2:
        system("clear");
        solicitarPista(cliente, IP, puerto, avion);
        abrirConsola(direccionServidor, cliente, IP, puerto, avion);
        break;
        case 3:
        system("clear");
        despegar(cliente, IP, puerto, avion);
        abrirConsola(direccionServidor, cliente, IP, puerto, avion);
        break;
        case 4:
        system("clear");
        aterrizar(cliente, IP, puerto, avion);
        abrirConsola(direccionServidor, cliente, IP, puerto, avion);
        break;
        case 5:
        system("clear");
        mostrarEstadoAvion(avion);
        abrirConsola(direccionServidor, cliente, IP, puerto, avion);
        break;
    }
}


