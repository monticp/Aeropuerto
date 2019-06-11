#ifndef AVION_H_INCLUDED
#define AVION_H_INCLUDED

typedef struct {
    char id [9];
    char modelo [20];
    int capMax;
    int cantCombustible;
    char estado;
}ST_AVION;

void parsearTextoParametro (const char * argv1, char * IP, char* strPuerto, int * puerto, char * ID, char * modelo, int * cantMaxComb );

void crearAvion (ST_AVION * avion);

void mostrarEstadoAvion (ST_AVION *avion);

char * armarMensaje(int cliente, char * IP, char * puerto, ST_AVION * avion, int charOpcion);

int recibirMensaje (int cliente, int opcion, ST_AVION * avion, int * pistaAsignada);

char strtoi (int N);

#endif // AVION_H_INCLUDED
