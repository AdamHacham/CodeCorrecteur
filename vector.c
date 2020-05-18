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

Vector vector_multiplication_scalaire(Vector A,int y,int (*pf)(int,int), int k){
  
 Vector self = NULL;
 self = malloc(sizeof(*self));
 self->size = A->size;
 self->elements = (int *) malloc((self->size)*sizeof(int));
 for(int i=0; i<self->size; i++)
 {
  *(self->elements+i) = (*pf)((*(A->elements+i)*y),k);
 }
 return self;
}

int vector_poid(Vector A)
{
 int res = 0;
 for(int i = 0; i<A->size; i++)
 {
  if(*(A->elements+i) != 0)
  {
   res++;
  }
 }
 return res;
}

int vector_compare(Vector A, Vector B){
 if(A->size != B->size){
  printf("La taille des vecteurs A et B est différents");
  return 0;
 }
 for(int i=0; i<A->size; i++){
  if(*(A->elements+i) != *(B->elements+i)){
   return 0;
  }
 }
 return 1;
}

int vector_compare_multiple(Vector A, Vector B, int k){
 
 for(int i=1; i<k+1; i++){
   if(vector_compare(vector_multiplication_scalaire(A,i,&GF,k),B) == 1){
   return 0;
  }
 }
 return 1;
}

Vector combine_vectors(Vector A, Vector B, int k){

 int size = A->size + B->size;
 int * tab = malloc(size*sizeof(int));
 int j = 0;
 for(int i=0; i<size; i++){
  if(i<A->size){
   tab[i] = A->elements[i];
  } else {
   tab[i] = B->elements[j];
   j++;
  }
 }
 return vector_init(size,tab,&GF,k);
}
