#include "func_cliente.h"

int conectar(int argc, char **argv){

  int mySockfd, status;
  struct sockaddr_in server_addr;

  if((mySockfd = socket(AF_INET, SOCK_STREAM, 0)) != -1){

    server_addr.sin_family = AF_INET;
    if(inet_pton(AF_INET, argv[2], &server_addr.sin_addr) == 1){
      server_addr.sin_port = htons(atoi(argv[1]));
      memset(&(server_addr.sin_zero), 0, 8);

      status = connect(mySockfd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr));
      if(!status) status = mySockfd;
      else status = ERRCONN;
    } else {
      status = ERRIP;
    }
  } else {
    status = ERRSOCK;
  }
  return status;
}
