#include <stdio.h>  
#include <stdlib.h> 
#include "vector.h"
#include "matrice.h"
#include "algcomb.h"

Matrice combinaison_list(int dim, int card, int k)
{
 Matrice mat = NULL;
 for(int i=0; i<card ;i++)
 {
  int * tab = itobase(i,k,dim);
  Vector self = vector_init(dim,tab,&GF,k);
  affiche(self);
  mat = matrice_add_vector(mat,self);  
 }
 return mat;

}

int * itobase(int nbr, int base, int dim){
  

  int * tab = (int *) malloc(dim*sizeof(int));  
  for(int i=dim-1; i>=0; i--)  
  {  
    tab[i] = nbr%base;  
    nbr = nbr/base;  
  } 
    
  return tab;
}
