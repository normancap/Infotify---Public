#ifndef SERVIDOR_H
#define SERVIDOR_H

  #include "common.h"
  #include "common_wsize.h"
  #include "func_usuarios.h"
  #include "func_canciones.h"


  enum OPCIONES {Registrar_Usuario = 1,Iniciar_Sesion,Listar_Canciones,Filtrar_Canciones,Reproducir_Cancion,Salir};
  typedef enum OPCIONES opciones;

  int cabecera(char *buffer);
  int eleccion(char *cadena);
  void operar(int opcion, char *buffer, User **users, int *cant_usuarios, int cliente_fd);
  void copiar_user_from_buff(User *dest, char *src);

#endif
// Ejecucion:
// Este servidor debe ejecutar primero
// Luego cuando este a la escucha y un cliente se conecte, mandara un mensaje de saludo
// El cliente mandara uno y luego en servidor mandara otro y ahi es donde se acaba la conexion para ese clientes
// Luego el servidor puede aceptar otro cliente que posiblemente estaba a la espera
// y asi puede ir atendiendo varios clientes
// si en una de sus conexiones el cliente manda la palabra "SALIRYA" el servidor termina esa conexiony tamb se apaga el mismo

//10/11/2024
//  se reduce el codigo juntando las funciones socket() bind() listen() en una funcion que pide var de dir_servidor y el puerto y devuelve el socket del Servidor
// se encapsula la funcion connect() solo pide el socket del servidor y devuelve el socket_cliente
