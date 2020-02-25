#include <stdio.h>
#include <stdlib.h>
#include "linalg.h"

int main(void)
{
    int tab[10]= {1,2,3,4,5,6,7,8,9};
    Matrice *self = 'NULL';
    self = matrice_init(3,3,tab,&GF,4);
    affiche(self);
    matrice_delete(self);
    self = matrice_transposee(self,4);
    affiche(self);
    return 0;
}
