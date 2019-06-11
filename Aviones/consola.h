#ifndef CONSOLA_H_INCLUDED
#define CONSOLA_H_INCLUDED
#include "avion.h"

#include <arpa/inet.h>
#include <sys/socket.h>

void abrirConsola(struct sockaddr_in direccionServidor, int cliente, char * IP, char*puerto, ST_AVION *avion, int * pistaAsignada);

#endif // CONSOLA_H_INCLUDED
