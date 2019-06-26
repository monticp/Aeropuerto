#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "aviones.h"
#define longMensajeEnviado 2



   char strtoi (int N){
        char salida;
        salida = N + 48;
        return salida;
    }


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

    void registrarAvion (ST_AVION * avion){
            if (avion->estado == 'h'){
                    avion->estado = 'g';
            }
    }

    void enviarMensaje (int cliente, int opcion){
            switch(opcion){
                case 0: // La solicitud se proceso exitosamente
                    send(cliente, "0", longMensajeEnviado, 0);
                break;
                case 2: // La pista fue cedida a cliente
                    send(cliente, "2", longMensajeEnviado, 0);
                break;
                case 3: // El avion despego
                    send(cliente, "3", longMensajeEnviado, 0);
                break;
                case 4: // El avion aterrizo
                    send(cliente, "4", longMensajeEnviado, 0);
                break;
            }
    }

    void mostrarEstadoDeAvion (ST_AVION * avion){
        switch(avion->estado){
                case 'h':
                    printf("'En Hangar'\n");
                break;
                case 'g':
                    printf(" 'Listo/Hangar'\n");
                break;
                case 'l':
                    printf(" 'Listo/Despegar'\n");
                break;
                case 'd':
                    printf(" 'Despegando'\n");
                break;
                case 'v':
                    printf(" 'En Vuelo'\n");
                break;
                case 'e':
                    printf(" 'Espera/Aterrizar'\n");
                break;
                case 'a':
                    printf(" 'Aterrizando'\n");
                break;
        }
    }
