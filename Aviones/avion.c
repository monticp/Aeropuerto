#include "avion.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#define longComb 10
#define tamanioMaxLinea 50
#define tamanioBufferMensaje 100
#define longMensajeRecibido 2
#define conteoCombustible 2
#define gastoCombustible 2


enum envioYRecepcionDeMensajes {OPERACIONEXITOSA, REGISTRACION, SOLICITUDDEPISTA, DESPEGUE, ATERRIZAJE, COMBUSTIBLE};


/*****************************************//**
*@fn  strtoi
convierte una cifra entera en un char
*@param int N
*@return una variable char
********************************************/
   char strtoi (int N){
        char salida;
        salida = N + 48;
        return salida;
    }

/******************************************//**
*@fn  * enteroACadena
convierte un número en una cadena
*@param int valor
*@param char *cadena
*@return cadena
********************************************/
    char * enteroACadena (int valor, char * cadena){
        int cont = 0;
        char cad [10];
        int aux = valor;
        char numero;
        while ((aux/10)!=0){
            cont ++;
            aux = aux/10;
        }
        cad[cont+1] = '\0';
        while ((valor/10)!=0){
            numero = (valor%10) + 48;
            cad[cont] = numero;
            valor = valor/10;
            cont--;
        }
        numero = (valor%10) + 48;
        cad[cont] = numero;
        strcpy(cadena,cad);
        return cadena;
    }

    /******************************************//**
*@fn  * armarMensaje
**EN esta función concatenamos (armaremos) una sola cadena con todos los datos.
*@param c1 int cliente
*@param c2 char *IP
*@param c3 char * puerto
*@param c4 ST_AVION * avion
*@param c5 int charOpcion
*@return bufferMensaje
********************************************/
    char* armarMensaje(int cliente, char * IP, char * puerto, ST_AVION * avion, int charOpcion){
        char * bufferMensaje = (char*)malloc(tamanioBufferMensaje);
        memset(bufferMensaje, '\0', tamanioBufferMensaje);
        char charCliente = strtoi(cliente);
        strncat(bufferMensaje, &charCliente, 1);
        strcat(bufferMensaje, ";");
        strcat(bufferMensaje, IP);
        strcat(bufferMensaje, ";");
        strcat(bufferMensaje, puerto);
        strcat(bufferMensaje, ";");
        strcat(bufferMensaje, avion->id);
        strcat(bufferMensaje, ";");
        char opcion;
        opcion = strtoi(charOpcion);
        strncat(bufferMensaje, &opcion, 1);
        strcat(bufferMensaje, ";");
        if (charOpcion == REGISTRACION){
            strcat(bufferMensaje, avion ->modelo);
            strcat(bufferMensaje, ";");
            strncat(bufferMensaje, &avion ->estado, 1);
            strcat(bufferMensaje, ";");
            char * cantMaxComb = (char*)malloc (longComb);
            strcpy(cantMaxComb, enteroACadena(avion->capMax, cantMaxComb));
            strcat(bufferMensaje, cantMaxComb);
            strcat(bufferMensaje, ";");
            char * cantComb = (char*)malloc (longComb);
            strcpy(cantComb, enteroACadena(avion->cantCombustible, cantComb));
            strcat(bufferMensaje, cantComb);
            strcat(bufferMensaje, ";");
            free(cantMaxComb);
            free(cantComb);
        }
        if (charOpcion == COMBUSTIBLE){
            char * cantComb = (char*)malloc (longComb);
            strcpy(cantComb, enteroACadena(avion->cantCombustible, cantComb));
            strcat(bufferMensaje, cantComb);
            strcat(bufferMensaje, ";");
            free(cantComb);
            }
        //printf("Mensaje: %s", bufferMensaje);
        return bufferMensaje;

    }

    /******************************************//**
*@fn  parsearLinea
**parsear la línea
*@param c1 FILE* pArchivo
*@param c2 char * variable
********************************************/
    void parsearLinea (FILE* pArchivo, char * variable){
        char lineaArchivo [tamanioMaxLinea];
        fgets(lineaArchivo, sizeof(lineaArchivo), pArchivo);
        strtok (lineaArchivo, ":");
        strcpy(variable, strtok (NULL, ";"));
    }


    /******************************************//**
*@fn  parsearTextoParametro
**parsea el texto
*@param c1 const char * argv1
*@param c2 char * IP
*@param c3 char* strPuerto
*@param c4 int * puerto
*@param c5 char * ID
*@param c6 char * modelo
*@param c7 int * cantMaxComb
********************************************/
void parsearTextoParametro (const char * argv1, char * IP, char* strPuerto, int * puerto, char * ID, char * modelo, int * cantMaxComb ){
    FILE * pArchivo = fopen(argv1, "r+");
    parsearLinea(pArchivo, IP);
    parsearLinea(pArchivo, strPuerto);
    (*puerto)=atoi(strPuerto);
    parsearLinea(pArchivo, ID);
    parsearLinea(pArchivo, modelo);
    char cantMaxCombust [8];
    parsearLinea(pArchivo, cantMaxCombust);
    *cantMaxComb = atoi(cantMaxCombust);
    fclose (pArchivo);
}

/******************************************//**
*@fn  ingresarEstado
**función que toma el valor por teclado, y modifica el estado del avión.
*@param c1 ST_AVION* avion
********************************************/
    void ingresarEstado (ST_AVION * avion){
        scanf("%c", &avion->estado);
        if ((avion->estado!='h')&&(avion->estado!='v')){
            printf("El estado ingresado no es vàlido");
            ingresarEstado(avion);
        }
    }

    /******************************************//**
*@fn  crearAvion
**función que crea un avion
*@param c1 ST_AVION * avion
********************************************/
    void crearAvion (ST_AVION * avion){
        printf("\n Ingrese el estado actual en el que se encuentra el avion ('h' para 'En Hangar' y 'v' para 'En Vuelo') \n");
        ingresarEstado(avion);
        printf("Ingrese la cantidad de combustible del avion \n");
        scanf("%i", &avion->cantCombustible);
    }

    /******************************************//**
*@fn  recibirMensaje
**función que recibe la opción por consola y determina la acción siguiente.
*@param c1 int cliente
*@param c2 int opcion
*@param c3 ST_AVION * avion
*@param c4 int * pistaAsignada
********************************************/
    int recibirMensaje (int cliente, int opcion, ST_AVION * avion){
                char * bufferRecibido = (char*)malloc(longMensajeRecibido);
                int bytesRecibidos = recv(cliente, bufferRecibido, sizeof(bufferRecibido), 0);
                if (bytesRecibidos <= 0) {
                    perror("El chabón se desconectó o bla.");
                    return 1;
                    }
                int aux;
                aux = atoi(bufferRecibido);
                switch (opcion){
                    case REGISTRACION:
                    if (aux==OPERACIONEXITOSA){
                            printf ("\n El avion se registrò correctamente\n");
                            if (avion->estado=='h'){
                                avion->estado = 'g';
                            }
                        }
                    break;
                    case SOLICITUDDEPISTA:
                        if (aux==OPERACIONEXITOSA){
                            printf ("\n Se realizò correctamente la solicitud de pista\n");
                        }
                        if (aux==SOLICITUDDEPISTA){
                            printf("\n Se asignò la pista a este avion. Por favor indique al piloto la acciòn a realizar.\n");
                            if (avion->estado == 'g'){
                                avion->estado = 'l';
                            }
                            else if (avion->estado == 'v'){
                                avion->estado = 'e';
                            }
                        }
                    break;
                    case DESPEGUE:
                        if (aux==OPERACIONEXITOSA){
                            printf ("\n La operacion se relizo exitosamente\n");
                            if (avion->estado == 'l'){
                                avion->estado = 'd';
                            }
                            else if (avion->estado == 'e'){
                                avion->estado = 'a';
                            }
                        }
                        if (aux==DESPEGUE){
                            printf ("\n El avion despegò satisfactoriamente\n");
                            avion->estado = 'v';
                        }
                        if (aux==ATERRIZAJE){
                            printf ("\n El avion aterrizo satisfactoriamente\n");
                            avion->estado = 'g';
                        }
                    break;
                }
                free(bufferRecibido);
        }

/*****************************************//**
*@fn  mostrarEstadoAvion
**muestra las caracteristicas del avion actual
**muestra, id, estado y cantidad de combustible
*@param c1 ST_AVION *avion
********************************************/
void mostrarEstadoAvion (ST_AVION *avion){
    printf("\nEl ID del avion es %s\n", avion->id);
    printf("El modelo del avion es %s\n", avion->modelo);
    printf("La capacidad màxima de combustible es %i\n", avion->capMax);
    printf("La cantidad de combustible del avion es %i\n", avion->cantCombustible);
    switch(avion->estado){
            case 'h':
                printf("El estado del aviòn es: 'En Hangar'\n");
            break;
            case 'g':
                printf("El estado del aviòn es: 'Listo/Hangar'\n");
            break;
            case 'l':
                printf("El estado del aviòn es: 'Listo/Despegar'\n");
            break;
            case 'd':
                printf("El estado del aviòn es: 'Despegando'\n");
            break;
            case 'v':
                printf("El estado del aviòn es: 'En Vuelo'\n");
            break;
            case 'e':
                printf("El estado del aviòn es: 'Espera/Aterrizar'\n");
            break;
            case 'a':
                printf("El estado del aviòn es: 'Aterrizando'\n");
            break;
    }
}


void registracion (int cliente, char * IP, char * puerto, ST_AVION * avion){
        char* msj1 = armarMensaje(cliente,IP,puerto, avion, REGISTRACION);
        send(cliente, msj1, tamanioBufferMensaje, 0);
        free(msj1);
        recibirMensaje(cliente, REGISTRACION, avion);
}

void solicitarPista (int cliente, char * IP, char * puerto, ST_AVION * avion){
        char* msj2 = armarMensaje(cliente,IP,puerto, avion, SOLICITUDDEPISTA);
        send(cliente, msj2, tamanioBufferMensaje, 0);
        free (msj2);
        enviarCombustible(cliente, IP, puerto, avion);
        if ((avion->estado=='g')||(avion->estado=='v')){
            if(avion->estado == 'g'){
                avion->estado = 'l';
            }
            else if (avion->estado == 'v'){
                avion->estado = 'e';
            }
            mostrarEstadoAvion(avion);
            recibirMensaje(cliente, SOLICITUDDEPISTA, avion);
            system ("clear");
            }
    }

    void despegar (int cliente, char * IP, char * puerto, ST_AVION * avion){
        if (avion->estado=='l'){
            printf("\n Se enviò la orden para despegar\n");
            char* msj3 = armarMensaje(cliente,IP,puerto, avion, DESPEGUE);
            send(cliente, msj3, tamanioBufferMensaje, 0);
            free (msj3);
            enviarCombustible(cliente, IP, puerto, avion);
            while(avion->estado!='v'){
                mostrarEstadoAvion(avion);
                recibirMensaje(cliente, DESPEGUE, avion);
                system ("clear");
                }
            }
    }


    void aterrizar (int cliente, char * IP, char * puerto, ST_AVION * avion){
        if (avion->estado=='e'){
            printf("\n Se enviò la orden para aterrizar\n");
            char* msj4 = armarMensaje(cliente,IP,puerto, avion, ATERRIZAJE);
            send(cliente, msj4, tamanioBufferMensaje, 0);
            free(msj4);
            enviarCombustible(cliente, IP, puerto, avion);
            while(avion->estado!='g'){
                mostrarEstadoAvion(avion);
                recibirMensaje(cliente, DESPEGUE, avion);
                system("clear");
                }
            }
    }

    void restarCombustible (ST_AVION * avion){
        while (1){
            while (((avion->cantCombustible-gastoCombustible)>=0)&&((avion->estado == 'd')||(avion->estado == 'v')||(avion->estado == 'e')||(avion->estado == 'a'))){
                avion->cantCombustible = avion->cantCombustible - gastoCombustible;
                sleep (conteoCombustible);
            }
            if ((avion->cantCombustible-gastoCombustible)<0){
                printf("\n El avion no posee combustible\n");
                system ("clear");
            }
        }
    }

    void enviarCombustible (int cliente, char * IP, char * puerto, ST_AVION * avion){
        char* msj5 = armarMensaje(cliente,IP,puerto, avion, COMBUSTIBLE);
        send(cliente, msj5, tamanioBufferMensaje, 0);
        free(msj5);
    }
