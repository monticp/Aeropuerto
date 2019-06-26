#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string.h>
#include "consola.h"

/******************************************//**
*@fn  abrirConsola
**Visualiza una consola donde se puede acceder a
** las listas de aviones y al usuario de la pista
*@param ST_TODASLASLISTAS * todasLasListas
********************************************/
void abrirConsola (ST_TODASLASLISTAS * todasLaslistas){
        int flag = 0;
        while (flag == 0){
            char opcion = "0";
                printf("\nBievenido al sistema de gestion de la torre de control.\n");
                printf("[1] - Mostrar lista de aviones registrados\n");
                printf("[2] - Mostrar lista de aterrizaje\n");
                printf("[3] - Mostrar lista de despegue\n");
                printf("[4] - Mostrar uso de pista\n");
                printf("[5] - Eliminar avion\n");
            opcion = getchar();
            switch (opcion){
                case '1':
                    system ("clear");
                    mostrarLista(&todasLaslistas->avionesRegistrados);
                    getchar();
                break;
                case '2':
                    system ("clear");
                    mostrarLista(&todasLaslistas->listaAterrizaje);
                    getchar();
                break;
                case '3':
                    system ("clear");
                    mostrarLista(todasLaslistas->colaDespegue);
                    getchar();
                break;
                case '4':
                    system ("clear");
                    if (todasLaslistas->pistaAsignada!= 0){
                        printf("\nLa pista està siendo utilizada por el aviòn ID: %i\n", todasLaslistas->pistaAsignada);
                    }
                    getchar();
                break;
                case '5':
                    system ("clear");
                    eliminarAvion(todasLaslistas);
                    getchar();
                break;
                default:
                 while (!getchar());
                break;
            }
        }
}
