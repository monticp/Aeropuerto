#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string.h>
#include <pthread.h>
#include "aviones.h"
#include "listaAviones.h"
#include "gestionPista.h"
#include "consola.h"
#define tamanioBufferMensaje 100


int main(void) {

    struct sockaddr_in direccionServidor;
    direccionServidor.sin_family = AF_INET;
    direccionServidor.sin_addr.s_addr = INADDR_ANY;
    direccionServidor.sin_port = htons(8080);

    int servidor = socket(AF_INET, SOCK_STREAM, 0);

    int activado = 1;
    setsockopt(servidor, SOL_SOCKET, SO_REUSEADDR, &activado, sizeof(activado));

    if (bind(servidor, (void*) &direccionServidor, sizeof(direccionServidor)) != 0) {
        perror("Falló el bind");
        return 1;
    }

    printf("Estoy escuchando\n");
    listen(servidor, 100);



    //------------------------------

	ST_LISTAAVIONES * listaAvion;
	crearLista(&listaAvion);
    ST_LISTAAVIONES * colaAterrizar;
    crearLista(&colaAterrizar);
    ST_COLA colaDespegar;
    crearCola(&colaDespegar);
    ST_TODASLASLISTAS todasLasListas;

    int IDReservaPista = 0;
    int cliente = 0;
    int contAviones = 0;

    aunarListas(&todasLasListas,&cliente, &IDReservaPista, listaAvion, colaAterrizar, &colaDespegar);

    pthread_t gestionPista;

    pthread_create(&gestionPista, NULL, (void*)gestionarPista, (void*)&todasLasListas);

    pthread_t consola;

    pthread_create(&consola, NULL, (void*)abrirConsola, (void*)&todasLasListas);
    while (1){

        struct sockaddr_in direccionCliente;
        unsigned int tamanioDireccion = sizeof(struct sockaddr_in);
        cliente = accept(servidor, (void*) &direccionCliente, &tamanioDireccion);

        todasLasListas.cliente = cliente;

        pthread_t gestionClientes;

        pthread_create(&gestionClientes, NULL,(void*)recibirMensajeEnHilo, (void*)&todasLasListas);


        printf("\n \t\tRecibí una conexión en %d!!\n", cliente);

        //close (servidor);
    }

	return 0;
}
