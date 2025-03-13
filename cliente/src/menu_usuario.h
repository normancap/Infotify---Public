/*!
 * @file    func_menu.h
 * @brief   Contiene las constantes simbolicas, los tipos de datos, los prototipos de funciones, las enumeraciones y las structs asi tambien como los cambios de nombres con typedef
 * @author  Grupo 4
 * @date    13/10/2024
 */

#ifndef MENU_USUARIO_H_
#define MENU_USUARIO_H_

#include "common.h"
#include <stdlib.h>

#define FIN 2
#define SESION_OK 1

#define INICIAR_SESION "iniciar_sesion"
#define REGISTRARSE "registrar_usuario"

typedef struct user{
    char username[25];
    char password[25];
} User;

int menu_usuario(int socket);

void pedir_user_pass(User *datos);
int respuesta_menu(char *buffer);

int comando_iniciar_sesion(int socket);
int comando_registrarse(int socket);
/*!
 * @brief Ingresa al menu principal
 *
 * @param[in] users Puntero a un puntero de la struct User que contiene la dirección del vector de usuarios
 * @param[in] cant_usuarios Puntero a int que contiene la cantidad de usuarios del vector
 * @return	  Devuelve int para ingresar al menu de usuario.
 */
// int menu(User **, int *);

/*!
 * @brief Imprime lineas con fines esteticos.
 *
 * @param[in] VOID
 * @return	  Devuelve void, solo imprime.
 */
// void separador();

/*!
 * @brief Solicita los datos del usuario que se loguée.
 *
 * @param[in] datos Puntero a struct User, direccion de la struct a completar
 * @return	  Devuelve void, modifica por referencia.
 */
// void pedirUserPass(User *);

/*!
 * @brief Compara los datos ingresados por el usuario para verificar si se trata de un usuario valido.
 *
 * @param[in] users Puntero a User, vector de usuarios
 * @param[in] cant_usuarios Entero
 * @return	  Devuelve int para ingresar al menu de usuario.
 */
// int iniciar_sesion(User *, int);

/*!
 * @brief Crea un nuevo usuario.
 *
 * @param[in] users Puntero a un puntero de la struct User que contiene la direccion del vector de usuarios
 * @param[in] cant_usuarios Puntero a int que contiene la cantidad de usuarios del vector
 * @return	  Devuelve int para ingresar al menu de usuario.
 */
// int registrarse(User **, int *);

/*!
 * @brief Libera la memoria del vector de usuarios.
 *
 * @param[in] users Puntero a struct User, el vector de usuarios
 * @return	  Devuelve void, modifica por referencia.
 */
// void salir(User *);

#endif
