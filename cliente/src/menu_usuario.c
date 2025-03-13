/*!
 * @file    func_menu.c
 * @brief   Contiene los cuerpos de las funciones a utilizar
 * @author  Grupo 4
 * @date    13/10/2024
 */

#include "menu_usuario.h"

int menu_usuario(int socket){
  int opcion = 0, verif = OK;

  while(verif == OK){
    printf("Bienvenidos a la app de musica infotify!!\nSeleccione una opcion para continuar\n\n1- Iniciar sesion\n2- Registrarse\n3- Salir\n\nSeleccione:");

    opcion = pedir_opcion();
    switch(opcion){
      case 1: verif = comando_iniciar_sesion(socket);
          break;
      case 2: verif = comando_registrarse(socket);
          break;
      case 3: verif = FIN;
          send(socket, SALIR, BUFFER_SIZE, 0);
          break;
      default: printf("Porfavor elija una de las opciones");
          separador();
      break;
    }

  }
  return verif;
}

void pedir_user_pass(User *datos){ // No se me ocurre que error podria haber al pedir datos
  printf("Ingrese nombre de usuario: ");
  scanf("%s", datos->username);        // se puede usar fgets
  printf("Ingrese su password: ");
  scanf("%s", datos->password);        // se puede usar fgets
}
int respuesta_menu(char *buffer){
  int value;
  char *token = NULL;

  token = strtok(buffer, "{");
  token = strtok(NULL, "}");

  if(!strcmp(token,"OK")) value = SESION_OK;
  else value = OK;

  return value;
}

int comando_iniciar_sesion(int socket){
  int value;
  User datos;
  char buffer[BUFFER_SIZE] = {0};
  printf("HOlaaaa\n");

  pedir_user_pass(&datos);
  sprintf(buffer, "%s {%s,%s}", INICIAR_SESION, datos.username, datos.password);

  send(socket, buffer, BUFFER_SIZE, 0);
  memset(buffer, 0, BUFFER_SIZE);
  recv(socket, buffer, BUFFER_SIZE, 0);
  value = respuesta_menu(buffer);
  if(value == SESION_OK){
    separador();
    printf("Bienvenido/a %s!!\n\n", datos.username);
  }else{
    printf("\nError: Datos ingresados erroneos\n");
    separador();
  }
  return value;
}

int comando_registrarse(int socket){
  int value;
  User datos;
  char buffer[BUFFER_SIZE] = {0};

  pedir_user_pass(&datos);
  sprintf(buffer, "%s {%s,%s}", REGISTRARSE, datos.username, datos.password);

  send(socket, buffer, BUFFER_SIZE, 0);
  memset(buffer, 0, BUFFER_SIZE);
  recv(socket, buffer, BUFFER_SIZE, 0);
  value = respuesta_menu(buffer);
  if(value == SESION_OK){
    separador();
    printf("Usuario registrado %s exitosamente!!\n\n", datos.username);
  }else{
    printf("\nError: usuario ya registrado\n");
    separador();
  }
  return value;
}
