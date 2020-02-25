#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "linalg.h"

struct Matrice {
   int ligne;
   int colonne;
   int * elements;
};

int GF(int a, int b)
{
    return a%b;
}

Matrice* matrice_init(int l, int c, int * elem, int (*pf)(int,int), int m)
{
  Matrice *self = NULL;
  self = malloc(sizeof(*self));
  assert(self != NULL);
  self->colonne = c;
  self->ligne = l;
  self->elements = (int *) malloc(l*c*sizeof(int));

  for (unsigned i = 0; i < l*c; ++i)
  {
   self->elements[i] = (*pf)(elem[i],m);
  }
  return self;
}

void matrice_delete(Matrice *self)
{
 free(self);
}

int matrice_colonne(Matrice *self)
{
 return self->colonne;
}

int matrice_ligne(Matrice *self)
{
 return self->ligne;
}

int * matrice_elements(Matrice *self)
{
 return self->elements;
}

void matrice_set_elements(Matrice *self, int * elem)
{
 self->elements = elem;
}

Matrice * matrice_transposee(Matrice *self,int n)
{
 int ligne = matrice_ligne(self);
 int colonne = matrice_colonne(self);
 int size = matrice_colonne(self)*matrice_ligne(self);
 int * elem = (int *) malloc(size*sizeof(int));
 int e=0;
 for(int j=0; j<colonne; j++)
 {
  for(int i=0; i<ligne; i++)
  {
   elem[e] = self->elements[i*colonne+j];
   e++;
  }
 }
 return matrice_init(colonne, ligne, elem, &GF, n);
}


void affiche(Matrice *self)
{
 printf("%d\n",matrice_colonne(self));
 for (unsigned i = 0; i < self->colonne*self->ligne; ++i)
 {
   if(i%matrice_colonne(self) == 0) 
   {
    printf("\n\n");
   }
   printf("  %d", self->elements[i]);
 }
 printf("\n\n");
}
