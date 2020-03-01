#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "vector.h"
#include "matrice.h"

Matrice matrice_add_vector(Matrice mat, Vector vector)
{
  Matrice self;
  self = mat;
  if (self == NULL)
  {
    self = malloc(sizeof(*self));   
    self->size = 0;
    self->vectors = (Vector *) malloc((self->size+1)*sizeof(Vector));
  } else {
    self->size = mat->size;
    self->vectors = (Vector *) realloc(self->vectors,(self->size+1)*sizeof(Vector));
    for(int i = 0 ; i<self->size ;i++) 
     {
      *(self->vectors+i) = *(mat->vectors+i);
     }    
  }
  *(self->vectors+self->size) = vector;
  self->size= self->size+1;  
  return self;
}

Matrice matrice_transpose(Matrice self, int k)
{
 Matrice tmp = NULL;
 int * tab = malloc((self->size+1)*sizeof(int)); 
 for(int i=0; i<self->vectors[0]->size; i++)
 {
  for(int j = 0; j<self->size ; j++)
  {
   tab[j] = self->vectors[j]->elements[i];
  }
  Vector vec = vector_init(self->size,tab,&GF,k);
  tmp = matrice_add_vector(tmp, vec);
 } 
 return tmp;
}


Vector vector_colonne(int c, Matrice self, int k)
{
 int * tab = malloc(self->size*sizeof(int));
 for(int i=0; i<self->size; i++)
 {
  tab[i] = self->vectors[i]->elements[c];
 }
 return vector_init(self->size,tab,&GF,k);
}

Matrice matrice_multiplication(Matrice A, Matrice B, int k)
{
 if(A->vectors[0]->size != B->size)
 {
  printf("Erreur : Veuillez verifier la taille des matrices que vous multipliez !!!");
  return NULL;
 }
 Matrice self = NULL;
 for(int j = 0; j<A->size ; j++)
 {
 Vector tmp = NULL;
 int * tab = malloc((B->size)*sizeof(int));
  for(int i = 0; i<B->size ; i++)
   {
    tab[i] = vector_scalaire(vector_colonne(i,B,k),A->vectors[j]);
   }
 tmp = vector_init(B->vectors[0]->size,tab,&GF,k);
 self = matrice_add_vector(self,tmp);
 free(tab);
 }

 return self;
}

void matrice_delete(Matrice self)
{
}

