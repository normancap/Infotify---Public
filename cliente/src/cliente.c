#include "func_cliente.h"
#include "menu_usuario.h"
#include "menu_canciones.h"

int main(int argc, char **argv){
  int cliente_fd, sesion;

  if(argc >= 2){

    cliente_fd = conectar(argc, argv);

    if(cliente_fd > 0){
      //////////////////////////////////////////////////////////////
      sesion = menu_usuario(cliente_fd);
      if(sesion != FIN) menu_canciones(cliente_fd);
      //////////////////////////////////////////////////////////////
      close(cliente_fd);
      printf("Se cierra el socket y termina el programa\n");
    } else {
      perror("error al conectarse demasiados clientes en cola o servidor no encontrado"); // se puede saber que fallo en el conectar();
      close(cliente_fd);
    }
  } else {
    printf("Debe ingresar un NRO de PUERTO y la dir IP del servidor\nEJ:@~ ./cliente 8081 127.0.0.1\n");
  }

  return 0;
}
