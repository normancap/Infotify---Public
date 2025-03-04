#ifndef FUNC_EJEC_SERV_H
#define FUNC_EJEC_SERV_H

  #include "common.h"
  #include <sys/socket.h>
  #include <sys/types.h>
  #include <arpa/inet.h>
  #include <netinet/in.h>

  #define CONNECTIONS_MAX 4

  #define ERRORSOCK -1
  #define ERRORBIND -2
  #define ERRORLIST -3

  int abrir_conection(struct sockaddr_in *my_addr, char *puerto);
  int aceptar_conexion(int server_fd);
#endif
