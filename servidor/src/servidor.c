#include "func_ejec_serv.h"
#include "func_servidor.h"
#include <unistd.h>

int main(int argc, char **argv){
  int status = 1, end_session = 0;
  int server_fd, cliente_fd;
  struct sockaddr_in server_addr;
  char buffer[BUFFER_SIZE] = "Hola buenas buenas\n";

  int nroFunc;
  int cant_usuarios = 0;
  User *users = NULL;

  if(argc < 2){
    printf("Debe ingresar un NRO de PUERTO\nEJ:@~ ./servidor 8081\n");
    return 1;
  }

  //Se leen los usuarios y se almacenan en el array de usuarios para usar durante la ejecucion
  obtenerUsuarios(&users, &cant_usuarios);

  server_fd = abrir_conection(&server_addr, argv[1]);

  if(server_fd > 1){
    printf("Se abrio la conexion\n");
    while(1){
      printf("Esperando conexion de un cliente\n");
      cliente_fd = aceptar_conexion(server_fd);
      if(cliente_fd == -1){
        printf("Error en aceptar conexion del cliente\n");
        continue;
      }

      status = recv(cliente_fd, buffer, BUFFER_SIZE, 0);
      while(status > 0 && !end_session){
        printf("se recibe: %s\n", buffer);
        if(strcmp(buffer, "salir { }") == 0){
          printf("Se cierra la sesion\n");
          end_session = 1;
        }
        nroFunc = cabecera(buffer);
        operar(nroFunc, buffer, &users, &cant_usuarios, cliente_fd);
        status = recv(cliente_fd, buffer, BUFFER_SIZE, 0);
      }
      close(cliente_fd);
      end_session = 0;
      printf("\nCierro el socket_cliente\n\n");
    }
  } else {
    printf("Error en open_conection()\n");  // se puede ver en q funcion fallo del abrir_conection()
    switch (server_fd) {
      case ERRORSOCK: printf("SOCKET\n");
      break;
      case ERRORBIND: printf("BIND\n");
      break;
      case ERRORLIST: printf("LISTEN\n");
      break;
      default: printf("Nose q fue lo q paso\n");
      break;
    }
  }
  free(users);

  return 0;
}
