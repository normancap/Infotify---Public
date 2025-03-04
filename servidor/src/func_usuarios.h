/*!
 * @file    func_usuarios.h
 * @brief   Definicion de prototipos de funciones y estructuras utilizadas para el manejo de usuarios
 * @author  Grupo 4
 * @date    15-10-2024
 */

#ifndef FUNC_USUARIOS_H
#define FUNC_USUARIOS_H

  #include "common.h"

  #define OK 0
  #define ERROR 1
  #define EXISTE 2
  #define NO_EXISTE 3
  #define SESION_OK -1

  typedef struct user{
      char username[25];
      char password[25];
  } User;

  /*!
   * @brief Copia los datos de un usuario fuente a un usuario destino
   *
   * @param dest Puntero al usuario destino
   * @param src Usuario fuente
   * @return
   */
  void copiarUsuario(User *dest, User src);

  /*!
   * @brief Almacena los usuarios de la base de datos en un arreglo dinamico
   *
   * @param users Puntero al arreglo de usuarios
   * @param cant_users Puntero a la cantidad de usuarios
   * @return OK si se pudo obtener los usuarios, ERROR si no se pudieron almacenar los usuarios
   */
  int obtenerUsuarios(User **users, int *cant_users);

  /*!
   * @brief Agrega un usuario al arreglo de usuarios y a la base de datos
   *
   * @param users Puntero al arreglo de usuarios
   * @param cant_users Puntero a la cantidad de usuarios
   * @param user Usuario a agregar
   * @return OK si se pudo agregar el usuario, ERROR si no se pudo agregar el usuario
   */
  int agregarUsuario(User **users, int *cant_users, User user);

  /*!
   * @brief Verifica si un usuario ya existe en el arreglo de usuarios
   *
   * @param users Arreglo de usuarios
   * @param cant_users Cantidad de usuarios
   * @param username Nombre de usuario a verificar
   * @return EXISTE si el usuario ya existe, NO_EXISTE si el usuario no existe
   */
  int existeUsuario(User *users, int cant_users, char *username);

  /*!
   * @brief Valida las credenciales de un usuario
   *
   * @param users Arreglo de usuarios
   * @param cant_users Cantidad de usuarios
   * @param user Usuario a validar
   * @return EXISTE si el usuario y la contraseña son correctos, NO_EXISTE si el usuario no existe o la contraseña es incorrecta
   */
  int validarUsuario(User *users, int cant_users, User user);

#endif //FUNC_USUARIOS_H
