#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "vector.h"

int GF(int a, int b)
{
    return a%b;
}

Vector vector_init(int c, int * elem, int (*pf)(int,int), int m)
{
  Vector self = NULL;
  self = malloc(sizeof(*self));
  assert(self != NULL);
  self->size = c;
  self->elements = (int *) malloc(c*sizeof(int));

  for (unsigned i = 0; i < c; ++i)
  {
   self->elements[i] = (*pf)(elem[i],m);
  }
  return self;
}

void vector_delete(Vector self)
{
 free(self);
}

int vector_size(Vector self)
{
 return self->size;
}

int * vector_elements(Vector self)
{
 return self->elements;
}

Vector vector_addition(Vector A, Vector B, int (*pf)(int,int), int k)
{
 if(A->size != B->size)
 {
  printf("Error vector_addition(Vector A, Vector B) : A != B");
  return NULL;
 }
 Vector self = NULL;
 self = malloc(sizeof(*self));
 self->size = A->size;
 self->elements = (int *) malloc((self->size)*sizeof(int));
 for(int i=0; i<self->size; i++)
 {
  *(self->elements+i) = (*pf)((*(A->elements+i) + *(B->elements+i)),k);
 }
 return self; 
}

int vector_scalaire(Vector A, Vector B)
{
 int res = 0;
 if (A->size != B->size)
 {
  fprintf( stderr, "Different size ? \n");
  exit( 0 );
 }
 for(int i = 0; i<A->size; i++)
 {
  res += *(A->elements+i) * *(B->elements+i);
 }
 return res;
}

void vector_set_elements(Vector self, int * elem)
{
 self->elements = elem;
}

void affiche(Vector self)
{
 for (unsigned i = 0; i < self->size; ++i)
 {
   printf("  %d", self->elements[i]);
 }
 printf("\n\n");
}
