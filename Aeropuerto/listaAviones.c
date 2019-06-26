#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "listaAviones.h"
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string.h>
#define longID 9
#define tamanioBufferMensaje 100
#define longCantComb 10

//1
/******************************************//**
*@fn crearLista
**Crea una lista apuntando la cabecera a NULL
*@param c1 ST_LISTAAVIONES**cabecera
*******************************************/
void crearLista (ST_LISTAAVIONES**cabecera){
        *cabecera = NULL;
}

//2
/******************************************//**
*@fn ST_LISTAAVIONES *crearNodo
**Crea un nodo.
*@param ST_AVION *avion
*@return nodo
********************************************/
ST_LISTAAVIONES * crearNodo (ST_AVION * avion) {
        ST_LISTAAVIONES * nodo = (ST_LISTAAVIONES*)malloc(sizeof(ST_LISTAAVIONES));
        nodo->avion = avion;
        nodo->ste = NULL;
        return nodo;
}
//3
/******************************************//**
*@fn crearCola
** Crea una cola apuntando tanto la cabecera como el fin a NULL
*@param ST_COLA *cola
********************************************/
void crearCola(ST_COLA * cola){
    cola->cabecera = NULL;
    cola->fin = NULL;
}

//4
/******************************************//**
*@fn agregarACola
**Crea nodo para agregar a la cola
*@param ST_COLA *cola
*@param ST_AVION *avion
********************************************/
void agregarACola (ST_COLA * cola, ST_AVION * avion){
    ST_LISTAAVIONES * nodo = crearNodo(avion);

    if(cola->cabecera==NULL){
        cola->cabecera = nodo;
    }
    else{
        cola->fin->ste = nodo;
    }
    cola->fin = nodo;
}

//5
/******************************************//**
*@fn insertarOrdenado
**inserta un nuevo nodo (avion) a la lista de aviones
*@param c1 ST_LISTAAVIONES**cabecera
*@param c2 ST_AVION avion
********************************************/
void insertarEnLista (ST_LISTAAVIONES ** cabecera, ST_AVION * avion){

    ST_LISTAAVIONES * nodo = crearNodo(avion);

    ST_LISTAAVIONES * aux = *cabecera;

    if (aux!=NULL){
            nodo->ste = *cabecera;
    }
    *cabecera = nodo;
}

//6
/******************************************//**
*@fn mostrarLista
**Muestra las caracteristicas del avion por pantalla
*@param ST_LISTAAVIONES**cabecera
********************************************/
void mostrarLista (ST_LISTAAVIONES**cabecera){
    ST_LISTAAVIONES * aux = *cabecera;
    if (aux!=NULL){
        printf("\nAVION:\n");
        printf("ID: %i\n",aux->avion->id);
        printf("Modelo: %s\n",aux->avion->modelo);
        printf("Estado:");
        mostrarEstadoDeAvion(aux->avion);
        printf("Cantidad de combustible: %i\n",aux->avion->cantCombustible);
    }
    while((aux!=NULL)&&(aux->ste!=NULL)){
        printf("\nAVION:\n");
        printf("ID: %i\n",aux->ste->avion->id);
        printf("Modelo: %s\n",aux->ste->avion->modelo);
        printf("Estado:");
        mostrarEstadoDeAvion(aux->ste->avion);
        printf("Cantidad de combustible: %i\n",aux->ste->avion->cantCombustible);
        aux = aux->ste;
    }
}

//7

/******************************************//**
*@fn ST_LISTAAVIONES * buscarIDEnLista
**Busca un avion de la lista de aviones
**por numero de identificacion.
*@param c1 int ID
*@param c2 ST_LISTAAVIONES ** cabecera
*@return Null si el avion no fue encontrado
*@return aux con la estructura del avion encontrado
********************************************/
ST_LISTAAVIONES * buscarIDEnLista (int ID, ST_LISTAAVIONES ** cabecera){
    ST_LISTAAVIONES * aux = *cabecera;

    while ((aux!=NULL) && (ID!=aux->avion->id)){
        aux = aux->ste;
    }
    return aux;
}

//8
/******************************************//**
*@fn ordenarPorCombustible
**Ordena la lista de aviones por cantidad de combustible
*@param c1 ST_LISTAAVIONES ** cabecera
*@param c2 ST_AVION avion
********************************************/
void ordenarPorCombustible (ST_LISTAAVIONES ** cabecera, ST_AVION * avion){
    ST_LISTAAVIONES * busqueda = buscarIDEnLista(avion->id, cabecera);
    if (busqueda!=NULL){
        perror("Elemento existente");
        return;
    }

    ST_LISTAAVIONES * nodo = crearNodo(avion);

    ST_LISTAAVIONES * aux = *cabecera;
    ST_LISTAAVIONES * nodoAnt = NULL;

    while ((aux!=NULL)&&(avion->cantCombustible>aux->avion->cantCombustible)){
            nodoAnt = aux;
            aux = aux->ste;
    }
    if(nodoAnt==NULL){
            *cabecera = nodo;
            nodo->ste = aux;
    }
    else {
            nodo->ste = aux;
            nodoAnt->ste = nodo;
    }
}

//9
/******************************************//**
*@fn solicitarPista
**la funcion recibe los datos del avion que socilita utilizar la pista,
**y lo coloca en la cola de despegar o en la lista de aterrizar segun el caso
*@param c1 ST_LISTAAVIONES ** listaAterrizar
*@param c2 ST_COLA * colaDespegar
*@param c3 ST_AVION * avion
********************************************/
void solicitarPista (ST_LISTAAVIONES ** listaAterrizar, ST_COLA * colaDespegar, ST_AVION * avion){
        if (avion->estado == 'v'){
            ordenarPorCombustible(listaAterrizar, avion);
            avion->estado = 'e';
            //mostrarLista(listaAterrizar);
        }
        else if (avion->estado == 'g'){
            agregarACola(colaDespegar, avion);
            avion->estado = 'l';
            //mostrarLista(&colaDespegar->cabecera);
        }
        else {
            printf("\n Estado del avion invalido para efectuar la operacion \n");
        }
}

//10
/******************************************//**
*@fn parsearMensaje
**Recibe un string de datos separados por punto
**y coma y selecciona dos que son necesarios
**para el proceso: ID del avion y tipo de mensaje
*@param c1 char * bufferMensaje
*@param c2 ST_AVION * avion
********************************************/
int parsearMensaje (char * bufferMensaje, ST_AVION * avion){
            strtok(bufferMensaje, ";");
            strtok(NULL, ";");
            strtok(NULL, ";");
            char id [longID];
            strcpy(id,strtok(NULL,";"));
            avion->id = atoi(id);
            char opcion;
            strcpy(&opcion,strtok(NULL, ";"));
            int Opcion = atoi (&opcion);
            return Opcion;
            }
//11
/******************************************//**
*@fn caracterizarAvion
**Obtiene de un string de datos serializados,
**separados por punto y coma, los parametros del avion
*@param c1 ST_AVION * avion
********************************************/
void caracterizarAvion (ST_AVION * avion){
                strcpy(avion->modelo,strtok(NULL, ";"));
                strcpy(&avion->estado,strtok(NULL, ";"));
                char cantMaxComb [longCantComb];
                strcpy(cantMaxComb,strtok(NULL, ";"));
                avion->capMax = atoi (cantMaxComb);
                char cantComb [longCantComb];
                strcpy(cantComb,strtok(NULL, ";"));
                avion->cantCombustible = atoi (cantComb);
}

//12
/******************************************//**
*@fn recibirMensajeEnHilo
**recibe los datos del cliente (avion) y sigue la opcion recibida
*@param c1 ST_TODASLASLISTAS * todasLasListas
********************************************/
void recibirMensajeEnHilo (ST_TODASLASLISTAS * todasLasListas){
            ST_AVION * avion = (ST_AVION*)malloc(sizeof(ST_AVION));
            char * bufferMensaje = (char*)malloc(tamanioBufferMensaje);
            int bytesRecibidos = recv(todasLasListas->cliente, bufferMensaje, tamanioBufferMensaje, 0);
            if (bytesRecibidos <= 0) {
                perror("El chabón se desconectó o bla.");
                return;
                }
            //printf("Mensaje: %s \n", bufferMensaje);
            int Opcion = parsearMensaje(bufferMensaje, avion);
            if (Opcion == 1){
                avion->cliente = todasLasListas->cliente;
                caracterizarAvion(avion);
                registrarAvion(avion);
                insertarEnLista(&todasLasListas->avionesRegistrados,avion);
                //mostrarLista(&todasLasListas->avionesRegistrados);
                enviarMensaje(avion->cliente, 0);
                free(bufferMensaje);
                }
        while (todasLasListas->avionEliminado!=avion->id){
            char * bufferMensaje = (char*)malloc(tamanioBufferMensaje);
            int bytesRecibidos = recv(avion->cliente, bufferMensaje, tamanioBufferMensaje, 0);
            if (bytesRecibidos <= 0) {
                perror("El chabón se desconectó o bla.");
                return;
                }
            //printf("Mensaje: %s \n", bufferMensaje);
            Opcion = parsearMensaje(bufferMensaje, avion);
            switch (Opcion){
                case 1:
                    enviarMensaje(avion->cliente, 2);
                    free(bufferMensaje);
                break;
                case 2:
                    //system ("clear");
                    //enviarMensaje(avion->cliente, 0);
                    solicitarPista(&todasLasListas->listaAterrizaje, todasLasListas->colaDespegue, avion);
                    //printf("\n Se copia el aviòn en una cola de espera para aterrizar u otra para despegar \n");
                    free(bufferMensaje);
                break;
                case 3:
                    todasLasListas->reservapista = avion->id;
                    //printf ("\n Se recibiò la orden para despegar del avion ID: %i\n", avion->id);
                    free(bufferMensaje);
                break;
                case 4:
                    todasLasListas->reservapista = avion->id;
                    //printf ("\n Se recibiò la orden para aterrizar del avion ID: %i\n", avion->id);
                    free(bufferMensaje);
                break;
                case 5:
                    avion->cantCombustible = atoi(strtok(NULL, ";"));
                    free(bufferMensaje);
                break;
            }
        }
        free(avion);
    }

    void eliminarAvion (ST_TODASLASLISTAS * todasLasListas){
            int ID = 0;
            printf("\n Ingrese el ID del avion que desea egresar\n");
            scanf ("%i", &ID);
            ST_LISTAAVIONES * aux = todasLasListas->avionesRegistrados;
            ST_LISTAAVIONES * ant = aux;
            while ((aux!=NULL)&&(aux->avion->id!=ID)){
                ant = aux;
                aux = aux->ste;
            }
            if (aux == NULL){
                perror("Avion no encontrado\n");
                return;
            }
            todasLasListas->avionEliminado = ID;
            if ((aux->avion->estado == 'g')||(aux->avion->estado=='v')){
                ant->ste = aux->ste;
                if(ant==aux){
                    todasLasListas->avionesRegistrados = aux->ste;
                }
                free(aux);
            }
    }
