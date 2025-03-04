/*!
 * @file    menu_usuario_funciones.c
 * @brief   Contiene los cuerpos de las funciones a utilizar
 * @author  Grupo 4
 * @date    13/10/2024
 */

#include "func_canciones.h"

void leerCanciones(char *nombre, CANCION **vec, int *cant){
    FILE *archivo = NULL;
    char linea[160] = {0};
    char *token = NULL;
    CANCION *aux = NULL;

    archivo = fopen(nombre, "r");
    if (archivo){

        while (fgets(linea, sizeof(linea), archivo)){

          if (linea[strlen(linea) - 1] == '\n')
              linea[strlen(linea) - 1] = '\0';
          aux = (CANCION *)realloc(*vec, sizeof(CANCION) * ((*cant) + 1));
          if (aux){
            *vec = aux;
            (*vec)[*cant].numero = *cant + 1;

            token = strtok(linea, ",");        // Se utiliza la funcion strtok la cual va diseccionando en pequeñas cadenas o tokens cuyo separador es "," o "\n" en el caso de la ultima
            strcpy((*vec)[*cant].tema, token); // Se va completando la struct con los valores obtenidos

            token = strtok(NULL, ",");
            strcpy((*vec)[*cant].artista, token);

            token = strtok(NULL, ",");
            strcpy((*vec)[*cant].album, token);

            token = strtok(NULL, ",");
            strcpy((*vec)[*cant].genero, token);

            token = strtok(NULL, ",");
            strcpy((*vec)[*cant].anio, token);

            (*cant)++;
          } else printf("Error: No hay memoria suficiente\n");
        }
    } else printf("Error al abrir el archivo\n");

    fclose(archivo);
}

void addCancion(char *buffer, CANCION cancion)
{
    char aux[130] = {0};
    sprintf(aux, "%-4d %-27.27s %-27.27s %-27.27s %-25.25s %-5.5s\n", cancion.numero, cancion.tema, cancion.artista, cancion.album, cancion.genero, cancion.anio); //121bytes

    strcat(buffer, aux);
}

void filtrarCanciones(int cliente_fd, CANCION *vector, int cantidad, int criterio, char *filtro)
{
    int i, j = 0, noHayMas = 0;
    char auxFiltro1[50] = {0};
    char auxFiltro2[50] = {0};
    char bufferC[BUFFER_SIZE] = {0};
    char bufferD[BUFFER_LIST] = {0};
    aMinuscula(auxFiltro1, filtro);

    for(i = 0; i < cantidad; i++){
        if(criterio == 1) aMinuscula(auxFiltro2, vector[i].artista);
        else if(criterio == 2) aMinuscula(auxFiltro2, vector[i].genero);

        if(strcmp(auxFiltro2, auxFiltro1) == 0){
          addCancion(bufferD, vector[i]);
          j++;
          if( j>=67 ){
            noHayMas = 1;
            if(i+1 == cantidad){
              sprintf(bufferC, "FIN {%d}", 121*j);
              send(cliente_fd, bufferC, BUFFER_SIZE, 0);
              send(cliente_fd, bufferD, 121*j,0);
            } else {
              sprintf(bufferC, "LEYENDO {%d}", 121*j);
              send(cliente_fd, bufferC, BUFFER_SIZE, 0);
              send(cliente_fd, bufferD, 121*j,0);
              j=0;
            }
            memset(bufferC, 0, BUFFER_SIZE);
            memset(bufferD, 0, BUFFER_LIST);
          }
        }
    }
    if(j<67 && j!= 0){
      sprintf(bufferC, "FIN {%d}", 121*j);
      send(cliente_fd, bufferC, BUFFER_SIZE, 0);
      send(cliente_fd, bufferD, 121*j,0);
    }else if(j==0 && noHayMas == 0){
      sprintf(bufferC, "FIN {%d}", 32);
      send(cliente_fd, bufferC, BUFFER_SIZE, 0);
      send(cliente_fd, "No hay canciones con este filtro\n", 32,0);
    }else{
      sprintf(bufferC, "FIN {%d}", 1);
      send(cliente_fd, bufferC, BUFFER_SIZE, 0);
      send(cliente_fd, "\n", 1,0);
    }
    printf("Se envia lo filtrado\n");
}
void aMinuscula(char *str1, char *str2){
    int i=0;
    while(str2[i]!= '\0'){
      str1[i] = tolower(str2[i]);
      i++;
    }
    str1[i] = '\0';
}
int copiarIdCancion(char *buffer){
  int i=0, start_id=0;
  char id[5];
  while(buffer[i] != '}'){
    if(buffer[i] == '{'){
      start_id = i+1;

    } else if(start_id){
      id[i-start_id] = buffer[i];
      if(buffer[i+1] == '}')
        id[i-start_id+1] = '\0';
    }
    i++;
  }
  return atoi(id);
}
void copiarFiltro(int *criterio, char *filtro, char *buffer){
  int i=0, start_criterio=0, start_filtro=0;
  while(buffer[i] != '}'){

    if(buffer[i] == '{'){
      start_criterio = i+1;

    } else if(buffer[i] == ','){
      start_filtro = i+1;
      *criterio = atoi(buffer+start_criterio);

    } else if(start_filtro){
      filtro[i-start_filtro] = buffer[i];
      if(buffer[i+1] == '}')
        filtro[i-start_filtro+1] = '\0';
    }
    i++;
  }
}
void enviarCancion(int cliente_fd, int id){
    int leidos = 0, value;
    char nombre[20];
    FILE *archivo = NULL;
    char bufferC[BUFFER_SIZE] = {0};
    char bufferD[BUFFER_SONG] = {0};

    sprintf(nombre, "media/%d.mp3", id);

    archivo = fopen(nombre, "rb");
    if(archivo){
        do{
          leidos = fread(bufferD, 1, BUFFER_SONG, archivo);
          if(feof(archivo)) sprintf(bufferC, "FIN {%d}", leidos);
          else sprintf(bufferC, "LEYENDO {%d}", leidos);

          value = send(cliente_fd, bufferC, BUFFER_SIZE, 0);
          if(value > 0){
            value = send(cliente_fd, bufferD, leidos, 0);
            if(value <= 0) printf("Error al enviar buffer de datos\n");
          } else printf("Error al enviar buffer cabecera\n");

        }while(!feof(archivo));

        fclose(archivo);
        printf("Se envio la cancion\n");
    } else printf("Error al abrir el archivo\n");
}

void listar_canciones(int cliente_fd, CANCION *canciones, int largo){
  int i, j=0, value;
  char bufferC[BUFFER_SIZE] = {0};
  char bufferD[BUFFER_LIST] = {0};

  for( i=0; i<largo; i++){
    addCancion(bufferD, canciones[i]);
    j++;
    if( j>=67 ){
      if(i+1 == largo){
        sprintf(bufferC, "FIN {%d}", 121*j);
        value = send(cliente_fd, bufferC, BUFFER_SIZE,0);
        if(value>0){
          value = send(cliente_fd, bufferD, 121*j,0);
          if(value<=0) printf("Error al enviar buffer de datos\n");
        } else printf("Error al enviar buffer de cabecera\n");
      } else {
        sprintf(bufferC, "LEYENDO {%d}", 121*j);
        value = send(cliente_fd, bufferC, BUFFER_SIZE,0);
        if(value>0){
          value = send(cliente_fd, bufferD, 121*j,0);
          if(value<=0) printf("Error al enviar buffer de datos\n");
        } else printf("Error al enviar buffer de cabecera\n");
        j=0;
      }

      memset(bufferC, 0, BUFFER_SIZE);
      memset(bufferD, 0, BUFFER_LIST);
    }
  }
  if(j<67){
    sprintf(bufferC, "FIN {%d}", 121*j);
    value = send(cliente_fd, bufferC, BUFFER_SIZE,0);
    if(value>0){
      value = send(cliente_fd, bufferD, 121*j,0);
      if(value<=0) printf("Error al enviar buffer de datos\n");
    } else printf("Error al enviar datos de cabecera\n");
  }
}
