#ifndef HEADER_COMMON_H_
#define HEADER_COMMON_H_
  #include <sys/types.h>
  #include <sys/socket.h>
  #include <stdio.h>
  #include <string.h>

  #define BUFFER_SIZE 100  // 8192 // 8KB
  // #define BUFFER_SIZE 8192
  #define BUFFER_SONG 8192 // 8KB        Para funcion enviar_cancion()
  #define BUFFER_LIST 8192 // 8KB        Para funcion Listar_cancion()

  #define OK 0

  #define SALIR "salir { }"

  void separador();
#endif
