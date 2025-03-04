#ifndef FUNC_CLIENTE_H
#define FUNC_CLIENTE_H

  #include <errno.h>
  #include <stdlib.h>
  #include <sys/types.h>
  #include <sys/socket.h>
  #include <arpa/inet.h>
  #include <unistd.h>
  #include <string.h>


  #define ERRSOCK -1
  #define ERRIP -2
  #define ERRCONN -3

  int conectar(int argc, char **argv);

#endif
