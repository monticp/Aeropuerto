El programa "Avión" lee a partir de un archivo txt "Archivo" los parámetros:
IP: Indica la dirección IP en la que se alojará el servidor,
puerto: Indica el puerto en el que se va a asignar el socket,
ID: Indica el identificador ùnico del avión,
Modelo: Indica el modelo del avión,
Capacidad máxima: Indica la capacidad máxima de combustible del avión en litros.

Apartir de los parámetros recibidos y otros ingresados por teclado, se generan el socket cliente y la estructura avión que contiene la información del avión en memoria dinámica.

El proceso se puede comunicar con otro proceso "Aeropuerto" que simula la torre de control, que va a asignar su única pista a un avión.


