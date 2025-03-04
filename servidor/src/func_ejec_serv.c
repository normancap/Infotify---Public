#include "func_ejec_serv.h"

int abrir_conection(struct sockaddr_in *my_addr, char *puerto){

  int sockfd, status;
  sockfd = socket(AF_INET, SOCK_STREAM, 0); //crea el socket conconfiguracion para IPV4 y TCP
  if(sockfd !=-1) {
    my_addr->sin_family = AF_INET;
    my_addr->sin_addr.s_addr = INADDR_ANY;
    my_addr->sin_port = htons(atoi(puerto));
    memset(&(my_addr->sin_zero), 0, 8);
    status = bind(sockfd, (struct sockaddr *)my_addr, sizeof(*my_addr));
    if(!status) {
      status = listen(sockfd, CONNECTIONS_MAX);
      if(!status){
        printf("Escuchando en puerto %d...\n", atoi(puerto));   // crer salida de status = ERROR o OK
        status = sockfd;
      } else status = ERRORLIST;
    } else status = ERRORBIND;
  } else status = ERRORSOCK;
  return status;
}

int aceptar_conexion(int sockfd){
  int newfd;
  struct sockaddr_in cliente_addr;
  socklen_t cliente_addr_len = sizeof(cliente_addr);

  if((newfd = accept(sockfd, (struct sockaddr *)&cliente_addr, &cliente_addr_len) )!= -1){
    printf("server conexión desde:  %s\n", inet_ntoa(cliente_addr.sin_addr));
  }
  return newfd;
}
