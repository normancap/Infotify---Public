#include "func_servidor.h"

int cabecera(char *buffer){
  int func;
  char *token = NULL;
  char nombreFunc[25];

  token = strtok(buffer, " ");
  strcpy(nombreFunc, token);
  func = eleccion(nombreFunc);

  return func;
}

int eleccion(char *cadena){
    int opcion;

    if (!(strcmp(cadena, "registrar_usuario"))) opcion = 1;
    else if (!(strcmp(cadena, "iniciar_sesion"))) opcion = 2;
    else if (!(strcmp(cadena, "listado_media"))) opcion = 3;
    else if (!(strcmp(cadena, "filtrar_media"))) opcion = 4;
    else if (!(strcmp(cadena, "reproducir_media"))) opcion = 5;
    if (!(strcmp(cadena, "salir"))) opcion = 6;
    return opcion;
}

void operar(int opcion, char *buffer, User **users, int *cant_usuarios, int cliente_fd){
  int i, flag = ERROR;
  int cant_canciones = 0, id_cancion = -1, encontrada = 0;
  User user;
  CANCION *canciones = NULL;

  switch (opcion){

    case Registrar_Usuario:
        copiar_user_from_buff(&user, buffer);
        memset(buffer, 0, BUFFER_SIZE);

        flag = existeUsuario(*users, *cant_usuarios, user.username);
        if(flag == NO_EXISTE){
          flag = agregarUsuario(users, cant_usuarios, user);
          if(flag == OK){
            printf("Usuario registrado exitosamente\n");
            flag = SESION_OK;
          }else{
            printf("Error: No hay suficiente memoria\n");
            flag = OK;
          }
        }else{
          printf("Error: usuario ya registrado\n");
          flag = OK;
        }

        if (flag == SESION_OK)
          send(cliente_fd, "registrar_usuario {OK}", BUFFER_SIZE,0);
        else
          send(cliente_fd, "registrar_usuario {ERROR_USUARIO_YA_REGISTRADO}", BUFFER_SIZE,0);

        break;
    case Iniciar_Sesion:
        copiar_user_from_buff(&user, buffer);
        printf("User: %s\n", user.username);
        printf("Pass: %s\n", user.password);
        memset(buffer, 0, BUFFER_SIZE);
        flag = existeUsuario(*users, *cant_usuarios, user.username);
        if(flag == EXISTE){
          if(validarUsuario(*users, *cant_usuarios, user) == EXISTE){
            printf("Usuario logueado exitosamente\n");
            flag = SESION_OK;
          } else {
            printf("Error: Datos erroneos\n");
            flag = OK;
          }
        }else{
          flag = OK;
        }

        if (flag == SESION_OK)
         send(cliente_fd, "iniciar_sesion {OK}", BUFFER_SIZE,0);
        else
         send(cliente_fd, "iniciar_sesion {ERROR_DATOS_ERRONEOS}", BUFFER_SIZE,0);

        break;
    case Listar_Canciones:
        memset(buffer, 0, BUFFER_SIZE);
        leerCanciones("media.csv", &canciones, &cant_canciones);

        listar_canciones(cliente_fd, canciones, cant_canciones);

        break;
    case Filtrar_Canciones:
        int criterio;
        char filtro[50];
        copiarFiltro(&criterio, filtro, buffer);
        memset(buffer, 0, BUFFER_SIZE);
        leerCanciones("media.csv", &canciones, &cant_canciones);

        filtrarCanciones(cliente_fd, canciones, cant_canciones, criterio, filtro);

        break;
    case Reproducir_Cancion:

        leerCanciones("media.csv", &canciones, &cant_canciones);
        id_cancion = copiarIdCancion(buffer);

        for( i=0; i<cant_canciones; i++){
          if(canciones[i].numero == id_cancion){
            encontrada = 1;
            sprintf(buffer,"reproducir_media {OK,%s}",canciones[i].tema);
            send(cliente_fd, buffer, BUFFER_SIZE,0);
            recv(cliente_fd, buffer, BUFFER_SIZE,0); //no nos interesa que recibimos aca solo tiene que hacerlo para continuar con el protocolo 2a2 en enviarCancion
            enviarCancion(cliente_fd, id_cancion);
            break;
          }
        }
        if(!encontrada) send(cliente_fd, "reproducir_media {ERROR_CANCION_NO_ENCONTRADA}", BUFFER_SIZE,0);

        break;
    case Salir:

        // buffer = SALIRYA y cierro todo
        break;

    default:
        memset(buffer, 0, BUFFER_SIZE);
        strcpy(buffer, "Comando incorrecto");
        break;
  }
  free(canciones);
}

void copiar_user_from_buff(User *dest, char *src){
  int i=0, start_user=0, start_pass=0;
  while(src[i] != '}'){
    if(src[i] == '{'){
      start_user = i+1;

    } else if(src[i] == ','){
      start_pass = i+1;
      dest->username[i-start_user] = '\0';

    } else if(start_user && !start_pass){
      dest->username[i-start_user] = src[i];

    } else if(start_pass){
      dest->password[i-start_pass] = src[i];
      if(src[i+1] == '}')
        dest->password[i-start_pass+1] = '\0';

    }
    i++;
  }
}
