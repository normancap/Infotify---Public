/*!
 * @file    menu_usuario_funciones.c
 * @brief   Contiene los cuerpos de las funciones a utilizar
 * @author  Grupo 4
 * @date    13/10/2024
 */

#include "menu_canciones.h"

int obtener_filtros(int *criterio, char *filtro){
  int value = ERROR;
  printf("\n1.Filtrar por artista\n2.Filtrar por genero\n\nSeleccione: ");
  *criterio = pedir_opcion();

  if(*criterio == 1 || *criterio == 2){
    printf("\nIngrese el filtro: ");
    fgets(filtro, 40, stdin);
    filtro[strcspn(filtro, "\n")] = '\0';
    value = OK;
  }else {
    printf("\nIngrese una opcino valida\n");
    separador();
  }
  return value;
}

void mostrar_encabezado(){
  printf("\n%-4s %-27s %-27s %-27s %-25s %-5s\n", "ID", "Cancion", "Artista", "Album", "Genero", "Anio");
  printf("--------------------------------------------------------------------------------------------------------------------------\n");
}

int buffer1(int socket, int *final, ssize_t *bytes_leidos){
  int value;
  char buffer[BUFFER_SIZE] = {0};
  char *token = NULL;
  value = recv(socket, buffer, BUFFER_SIZE, 0);
  if(value>0){
    token = strtok(buffer,"{");
    if(!strcmp(token, "FIN ")) *final = 1;

    token = strtok(NULL,"}");
    *bytes_leidos = atoi(token);
  }else value = ERROR;

  return value;
}

int recepcion_cancion(char *buffer, char *nombre_cancion){
  int value = ERROR;
  char *token = NULL;
  token = strtok(buffer,"{");
  token = strtok(NULL,",}");  // hasta aca nos fijamos si recibimos OK o ERROR por si encontro o no la cancionID que le pedimos
  if(!strcmp(token,"OK")){    // si es OK habra un segundo dato que se puede sustraer que seria el NOmbre de la cancion
    token = strtok(NULL,"}");
    strcpy(nombre_cancion,token);
    value = OK;
  }
  return value;
}

void comando_reproducir(int socket){
  FILE *cancion = NULL;
  ssize_t bytes_leidos;
  char buffer[BUFFER_SIZE] = {0};
  char buffer2[BUFFER_SONG] = {0};
  int value, cancionId, final_cancion = 0;
  char ruta_cancion[60] = {0};
  char nombre_cancion[40] = {0};

  printf("Ingrese nro de cancion a reproducir: ");
  scanf("%d", &cancionId);
  sprintf(buffer, "%s {%d}", REPRODUCIR, cancionId);
  // OK
  send(socket, buffer, BUFFER_SIZE, 0);
  memset(buffer, 0, BUFFER_SIZE);
  recv(socket, buffer, BUFFER_SIZE, 0);

  value = recepcion_cancion(buffer, nombre_cancion);
  if(value == OK){

    sprintf(buffer, "%s {%d}", REPRODUCIR, cancionId);
    send(socket, buffer, BUFFER_SIZE, 0);                         // este send ya no importa pero tiene q enviar algo
    memset(buffer, 0, BUFFER_SIZE);
    sprintf(ruta_cancion,"./media/%s.mp3", nombre_cancion);       //ejecutar desde fuera de bin
    cancion = fopen(ruta_cancion, "wb");
    if(cancion!= NULL){
    // comienza protocolo 2a2
      while(!final_cancion){
        value = buffer1(socket, &final_cancion, &bytes_leidos);//
        if(value>0){
          recv(socket, buffer2, bytes_leidos, 0);
          fwrite(buffer2, sizeof(char), bytes_leidos, cancion);
        }else{
          printf("Hubo un error en recibir el buffer1\n");
          value = -1;
          final_cancion = 1;
        }
      }
      if(value>0)printf("%s\n", "Archivo recibido!");
      else printf("Descarga de archivo incompleta!\n");
      fclose(cancion);

    }else printf("Error al abrir %s\n", ruta_cancion);
  }else printf("No se encontro cancion en servidor\n");
  separador();
}

void comando_filtrar(int socket){
  int criterio, value, final = 0;
  ssize_t leidos = 0;
  char buffer[BUFFER_SIZE] = {0};
  char buffer2[BUFFER_LIST] = {0};
  char filtro[40] = {0};

  value = obtener_filtros(&criterio, filtro);
  if(value == OK){
    sprintf(buffer, "%s {%d,%s}", FILTRAR, criterio, filtro);
    send(socket, buffer, BUFFER_SIZE, 0);
    //OK
    mostrar_encabezado();
    while(!final){
      value = buffer1(socket, &final, &leidos);
      if(value>0){
        value = recv(socket, buffer2, leidos, 0);
        if(value>0){
          printf("%s",buffer2);
          memset(buffer2, 0, BUFFER_LIST);
        }
      }else{
        printf("Hubo un error en recibir el buffer1\n");
        value = -1;
        final = 1;
      }
    }
  }
  separador();

}

void comando_listar(int socket){
  int final = 0, value;
  ssize_t leidos = 0;
  char buffer2[BUFFER_LIST] = {0};

  send(socket, "listado_media {}", BUFFER_SIZE, 0);
  //Aca ya empieza el protocolo de comunicacion 2a2
  mostrar_encabezado();
  while(!final){
    value = buffer1(socket, &final, &leidos);
    if(value>0){
      value = recv(socket, buffer2, leidos, 0);
      if(value>0){
        printf("%s", buffer2);
        memset(buffer2, 0, BUFFER_LIST);
      }else printf("Error en recibir datos del buffer2\n");
    }else{
      printf("Hubo un error en recibir el 1er buffer\n");
      value = -1;
      final = 1;
    }
  }
  separador();
}

void menu_canciones(int socket)
{
    int opcion = 0; // Opcion del menu
    do
    {
        switch (opcion)
        {
        case 0:
            printf("1.Listar canciones\n");
            printf("2.Filtrar canciones\n");
            printf("3.Reproducir cancion\n");
            printf("4.Salir\n\n");
            printf("Seleccione: ");
            opcion = pedir_opcion();
            break;
        case 1: comando_listar(socket);
            opcion = 0;
            break;
        case 2: comando_filtrar(socket);
            opcion = 0;
            break;
        case 3: comando_reproducir(socket);
            opcion = 0;
            break;
        case 4: printf("Ha seleccionado 4, se saldra de Infotify!!\n");
            send(socket, SALIR, BUFFER_SIZE, 0);
            opcion = 5;
            break;
        default:
            printf("Ingrese una opcion valida\n");
            separador();
            opcion = 0;
            break;
        }
    } while (opcion != 5);
}
