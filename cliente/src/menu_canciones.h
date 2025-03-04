/*!
 * @file    menu_usuario.h
 * @brief   Contiene las constantes simbolicas, los tipos de datos, los prototipos de funciones, las enumeraciones y las structs asi tambien como los cambios de nombres con typedef
 * @author  Grupo 4
 * @date    13/11/2024
 */

#ifndef MENU_CANCIONES_H_
#define MENU_CANCIONES_H_

  #include <stdlib.h>
  #include "header_common.h"

  #define ERROR -1

  #define LISTAR "listado_media"
  #define FILTRAR "filtrar_media"
  #define REPRODUCIR "reproducir_media"

  #define ERRLISTAR "ERROR_ARCHIVO_NO_ENCONTRADO"
  #define ERRFILTRAR "ERROR_FILTRO_NO_ENCONTRADO"
  #define ERRREPRODUCIR "ERROR_CANCION_NO_ENCONTRADA"
  #define RUTA "../media/"

  int buffer1(int socket, int *final, ssize_t *bytes_leidos);
  int recepcion_cancion(char *buffer, char *nombre_cancion);
  int obtener_filtros(int *criterio, char *filtro);
  void mostrar_encabezado();

  void comando_reproducir(int socket);
  void comando_filtrar(int socket);
  void comando_listar(int socket);

  void menu_canciones(int socket);


// ----------------------------------------------------------------------------------------
/*!
 * @brief Abre el archivo csv para rellenar el vector a utilizar.
 *
 * @param[in] nombre Puntero a char, indica el nombre del archivo de canciones
 * @param[in] vec Puntero a puntero de struct CANCION, pasa la direccion del vector de canciones
 * @param[in] cant Puntero a entero, indica la cantidad de canciones del vector
 * @return	  Devuelve void, modifica por referencia.
 */
// void leerCanciones(char *, CANCION **, int *);

/*!
 * @brief El menu de seleccion del usuario una vez ingresado al sistema.
 *
 * @param[in] vector_canciones Puntero a CANCION, es el vector de canciones
 * @param[in] cant Entero, indica la cantidad de canciones
 * @return	  Devuelve void, modifica por referencia.
 */
// void menuUsuario(CANCION *, int);

/*!
 * @brief Imprime solamente el elemento seleccionado.
 *
 * @param[in] cancion_selecc una struct del tipo CANCION
 * @return	  Devuelve void ya que su objetivo es imprimir.
 */
// void imprimirCancion(CANCION);

/*!
 * @brief Recorre todo el vector e imprime cada uno de los elementos, es decir, las canciones
 *
 * @param[in] vec Puntero a CANCION, es el vector de canciones
 * @param[in] cant Entero, cantidad de canciones
 * @return	  Devuelve void ya que su objetivo es imprimir.
 */
// void imprimirCanciones(CANCION *, int);

/*!
 * @brief Copia el contenido de otra struct CANCION por referencia
 *
 * @param[in] vec Direccion de una struct CANCION
 * @param[in] pos Entero
 * @param[in] cancion_cargada Struct CANCION
 * @return	  Devuelve void, solamente se encarga de modificar por referencia.
 */
// void copiarCancion(CANCION *, int, CANCION);

/*!
 * @brief Filtra las canciones segun el criterio ingresado por el usuario.
 *
 * @param[in] vector Array de canciones
 * @param[in] cantidad Cantidad de canciones del array
 * @param[in] criterio Criterio de filtrado (1: Artista, 2: Genero)
 * @param[in] filtro Filtro a aplicar
 * @return	  Devuelve void ya que su objetivo es imprimir.
 */
// void filtrarCanciones(CANCION *vector, int cantidad, int criterio, char *filtro);
#endif
