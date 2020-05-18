#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "code.h"

const char* function_Strings[] = {"HammingCode", "CodeParite", "DistanceMinimal", "Code", "ReedMuller"}; 

int main()
{
 printf("all\n");
 Code c = nouveauCode(7,4,2);
 printf("all\n");
 ecrire_fichier("hamming",c);
 printf("all\n");
 
}
