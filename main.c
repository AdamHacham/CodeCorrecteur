#include <stdio.h>
#include <stdlib.h>
#include "vector.h"
#include "matrice.h"
#include "algcomb.h"

int main(void)
{
    int tab[10] = {1,2,3,4,5,6,7,8,9,1};
    int *tav;
    Vector self = NULL;
    Vector self1 = NULL;
    Vector self2 = NULL;
    self = vector_init(10,tab,&GF,4);
    self1 = vector_init(10,tab,&GF,4);
    self2 = vector_addition(self,self1,&GF,4);
    affiche(self2);

    Matrice mat = NULL;
    Matrice mat1 = NULL;
    Matrice mat2 = NULL;
    mat = combinaison_list(3,8,2);    
    int res = vector_scalaire(self,self1);
    printf("res = %d \n",mat->size);

    mat1 = matrice_transpose(mat,2);
    mat2 = matrice_multiplication(mat,mat1,4);

    affiche(mat2->vectors[0]);
    affiche(mat2->vectors[1]);
    affiche(mat2->vectors[2]);
    affiche(mat2->vectors[3]);
    affiche(mat2->vectors[4]);
    affiche(mat2->vectors[5]);
    affiche(mat2->vectors[6]);
    affiche(mat2->vectors[7]);

    vector_delete(self);
    vector_delete(self2);

    return 0;
}
