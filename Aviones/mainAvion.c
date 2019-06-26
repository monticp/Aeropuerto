#include <stdlib.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <pthread.h>
#include "consola.h"
#include "avion.h"
#define LongIP 15
#define LongID 9
#define LongModelo 12
#define LongPuerto 4


int main(int argc, char * argv []) {

    char *IP = (char*)malloc (LongIP);
    char * strPuerto = (char*)malloc (LongPuerto);
    int puerto = 0;
    ST_AVION avion;

    parsearTextoParametro(argv [1], IP, strPuerto, &puerto, avion.id, avion.modelo, &avion.capMax);

    crearAvion(&avion);

	struct sockaddr_in direccionServidor;
	direccionServidor.sin_family = AF_INET;
	direccionServidor.sin_addr.s_addr = inet_addr(IP);
	direccionServidor.sin_port = htons(puerto);

	int cliente = socket(AF_INET, SOCK_STREAM, 0);

    pthread_t gestionCombustible;

    pthread_create(&gestionCombustible, NULL, (void*)restarCombustible, (void*)&avion);

    system ("clear");

    abrirConsola(direccionServidor, cliente, IP, strPuerto, &avion);

    return 0;
}
