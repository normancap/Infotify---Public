/*!
 * @file    func_usuarios.c
 * @brief   Implementacion de las funciones utilizadas para el manejo de usuarios
 * @author  Grupo 4
 * @date    15-10-2024
 */

#include "func_usuarios.h"

void copiarUsuario(User *dest, User src){
    strcpy(dest->username, src.username);
    strcpy(dest->password, src.password);
}

int obtenerUsuarios(User **users, int *cant_users){
    FILE *db;
    User aux;
    User *auxp = NULL;
    db = fopen("usuarios.db", "rb");
    if(db == NULL)
        return OK;

    while(feof(db)==0){
        fread(&aux, sizeof(User), 1, db);
        if(feof(db)==0){
            *cant_users += 1;
            auxp = realloc(*users, sizeof(User)*(*cant_users));
            if(auxp == NULL)
              return ERROR;

            *users = auxp;
            copiarUsuario(&((*users)[*cant_users-1]), aux);
        }
    }
    fclose(db);
    return OK;
}

int agregarUsuario(User **users, int *cant_users, User user){
    FILE *db;
    User *auxp = NULL;
    db = fopen("usuarios.db", "ab");
    if(db == NULL)
        return ERROR;

    (*cant_users) += 1;
    auxp = realloc(*users, sizeof(User)*(*cant_users));
    if(auxp == NULL)
      return ERROR;

    *users = auxp;
    copiarUsuario(&((*users)[*cant_users-1]), user);
    fwrite(&user, sizeof(User), 1, db);

    fclose(db);
    return OK;
}

int existeUsuario(User *users, int cant_users, char *username){
    for(int i=0; i<cant_users; i++){
        if(strcmp(users[i].username, username)==0)
            return EXISTE;
    }
    return NO_EXISTE;
}

int validarUsuario(User *users, int cant_users, User user){
    for(int i=0; i<cant_users; i++){
        if(strcmp(users[i].username, user.username)==0 && strcmp(users[i].password, user.password)==0)
            return EXISTE;
    }
    return NO_EXISTE;
}
