#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "interface.h"

int main()
{
    char buffer[TAILLE_BUFFER];
    printf("\nInterpreteur de commande pour Code correcteur \nTaper \"quit\" pour quitter\n");
    while(1)
    {
       printf("> ");
       fgets(buffer,150,stdin);
       buffer[strlen(buffer)-1]='\0';
       char *variables = malloc(sizeof variables);
       char *functions = malloc(sizeof functions);
       char **param = malloc(3 * sizeof *param);
       for(int k = 0;k<3; k++){
        param[k] = malloc(3*sizeof **param);
       }
       int z=traitement_buffer(buffer,functions,variables,param);
       commande_client(buffer,variables,functions,param,z);
   }
}
