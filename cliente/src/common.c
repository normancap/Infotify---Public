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
    while ((c = getchar()) != '\n' && c != EOF);
  }
  value = atoi(opcionV);
  return value;
}
