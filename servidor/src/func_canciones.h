/*!
 * @file    menu_usuario.h
 * @brief   Contiene las constantes simbolicas, los tipos de datos, los prototipos de funciones, las enumeraciones y las structs asi tambien como los cambios de nombres con typedef
 * @author  Grupo 4
 * @date    13/10/2024
 */

#ifndef MENU_USUARIO_H
#define MENU_USUARIO_H

  #include "common.h"
  #include <ctype.h>
  #include "common_wsize.h"


  typedef struct cancion
  {
    int numero;
    char tema[50];
    char artista[50];
    char album[50];
    char genero[25];
    char anio[5];
  } CANCION;

  /*!
   * @brief Abre el archivo csv para rellenar el vector a utilizar.
   *
   * @param[in] nombre Puntero a char, indica el nombre del archivo de canciones
   * @param[in] vec Puntero a puntero de struct CANCION, pasa la direccion del vector de canciones
   * @param[in] cant Puntero a entero, indica la cantidad de canciones del vector
   * @return	  Devuelve void, modifica por referencia.
   */
  void leerCanciones(char *, CANCION **, int *);

  /*!
   * @brief Añade el contenido de una cancion a una cadena de caracteres.
   *
   * @param[in] buffer Cadena donde se va a añadir la cancion
   * @param[in] cancion Cuerpo de la cancion a añadir
   * @return	  Devuelve void, solamente se encarga de modificar por referencia.
   */
  void addCancion(char *buffer, CANCION cancion);

  /*!
   * @brief Filtra las canciones segun el criterio ingresado por el usuario.
   *
   * @param[in] vector Array de canciones
   * @param[in] cantidad Cantidad de canciones del array
   * @param[in] criterio Criterio de filtrado (1: Artista, 2: Genero)
   * @param[in] filtro Filtro a aplicar
   * @return	  Devuelve void ya que su objetivo es imprimir.
   */
  void filtrarCanciones(int cliente_fd, CANCION *vector, int cantidad, int criterio, char *filtro);

  void aMinuscula(char *str1, char *str2);

  void enviarCancion(int socket, int id);

  void listar_canciones(int cliente_fd, CANCION *canciones, int largo);

  int copiarIdCancion(char *buffer);

  void copiarFiltro(int *criterio, char *filtro, char *buffer);

#endif
