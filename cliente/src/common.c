#include "common.h"
#include <stdlib.h>

void separador(){
    printf("\n---------------------------------------------\n\n");
}

int pedir_opcion(){
  char opcionV[3] = {0};
  int c = 0, value = 0;
  fgets(opcionV, 3, stdin);

  if(strchr(opcionV,'\n')){
    opcionV[strcspn(opcionV, "\n")] = '\0';
  } else {
    c = getchar();
    while ( c != '\n' && c != EOF) c = getchar();
  }
  value = atoi(opcionV);
  if(value == 0) value = -1;
  return value;
}
