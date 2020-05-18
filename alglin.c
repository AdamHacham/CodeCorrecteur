#include <stdio.h>
#include <stdlib.h>
#include "vector.h"
#include "matrice.h"
#include "algcomb.h"
#include "alglin.h"

Matrice triangularise_mat(Matrice self, int k)
{
// int ind = 0;
 int var = 1;
 if(self == NULL){
  printf("la matrice donnée est null");
  return NULL;
 }
 Matrice mat = NULL;
 Matrice tmp = NULL;
 tmp = simplification_mat(self,k);
 if(tmp->size < tmp->vectors[0]->size){
  printf("Veuillez revoir la matrice rentré");
  return tmp;
 }
  int tab[tmp->vectors[0]->size];
  for(int i=0; i<tmp->vectors[0]->size; i++){
   tab[i]=0;
  }
  int ind = min_colonne_matrice(tmp,0);
  printf("indice : %d\n", ind);
  mat = matrice_add_vector(mat,tmp->vectors[ind]);
//  mat1= matrice_add_vector(mat1,vector_init(4,tab,&GF,k)); 
  for(int j=0; j<tmp->vectors[0]->size-1; j++){
    printf("______________Début___Boucle j : %d \n_____________",j);
//         Matrice mat1 = NULL;

    for(int i=0; i<tmp->size; i++){

        printf("_____________DEBUT__Boucle i : %d \n",i);
    if(vector_compare(mat->vectors[j],tmp->vectors[i]) || vector_exists(mat,tmp->vectors[i])){
    tmp->vectors[i] = vector_init(tmp->vectors[0]->size,tab,&GF,k);
    affiche(tmp->vectors[i]);
    continue;
    }
//    affiche(tmp->vectors[i]);

    Vector A = vector_multiplication_scalaire(mat->vectors[j],tmp->vectors[i]->elements[j],&GF,k);
    Vector B = vector_multiplication_scalaire(tmp->vectors[i],-(mat->vectors[j]->elements[j]),&GF,k);
    tmp->vectors[i] = vector_addition(A,B,&GF,k);
//    mat1 = matrice_add_vector(mat1,vector_addition(A,B,&GF,k));
        affiche(tmp->vectors[i]);
       // printf("________________FIN__Boucle i : %d \n________________",i);

   }
//  tmp->size = tmp->size - 1;
  ind = min_colonne_matrice(tmp,var++);
  printf("indice : %d\t", ind);
  printf("var : %d\t", var);
  affiche(tmp->vectors[ind]);
  mat = matrice_add_vector(mat,tmp->vectors[ind]);
  //tmp = mat1;
  //    printf("_____________Fin Boucle j : %d______________ \n",j);
 }
 return mat;
}


Matrice simplification_mat(Matrice self,int k)
{
 if(self == NULL) return NULL;
 Matrice tmp = NULL;
 Matrice mat = NULL;
 tmp = matrice_transpose(self,k);
 for(int i=0 ; i<tmp->size; i++){
  if (vector_null(tmp->vectors[i]) == 0 && vector_exists(mat,tmp->vectors[i]) != 1){
    mat = matrice_add_vector(mat,tmp->vectors[i]);
  }
 affiche(tmp->vectors[i]);
 }
 return mat;
}

int vector_exists(Matrice self, Vector v){

 if(self == NULL){
  return 0;
 }
 for(int j=0; j<self->size; j++){
  if(vector_compare(self->vectors[j],v) == 1){
    return 1;
  }
 }
 return 0;
}

int vector_null(Vector self){
 for(int i=0; i<self->size;i++){
  if(self->elements[i] != 0){
   return 0;
  }
 }
 return 1;

}

int min_colonne_matrice(Matrice A, int indice_colonne){
 int elem = max_colonne_matrice(A,indice_colonne);
 printf("elem : %d\n",elem);
 int indice_vect= 0;
 for(int i=0; i<A->size; i++){
  if(A->vectors[i]->elements[indice_colonne] <= elem && A->vectors[i]->elements[indice_colonne] != 0)
  {
   elem = A->vectors[i]->elements[indice_colonne];
   indice_vect = i;
  } 
 }
 return indice_vect; 
}

int max_colonne_matrice(Matrice A, int indice_colonne){
 int elem = 0;
 for(int i=0; i<A->size; i++){
  if(A->vectors[i]->elements[indice_colonne] > elem)
  {
   elem = A->vectors[i]->elements[indice_colonne];
  }
 }
 return elem;
}


int colonne_null(Matrice A, int indice_colonne){

 for(int i=0; i<A->size; i++){
  if(A->vectors[i]->elements[indice_colonne] != 0){
   return 0;
  }
 }
 return 1;

}

Matrice swap_vector(Matrice A, int i, int j){

 Vector tmp = NULL;
 tmp = A->vectors[i];
 A->vectors[i] = A->vectors[j];
 A->vectors[j] = tmp; 
 
 return A;
}

Matrice matrice_identite(int n){
 Matrice self = NULL;
 int * tab = malloc(n*sizeof(int));
 for(int i = 0; i<n; i++){
  if(i == 0){
   tab[i]=1;
  }else {
   tab[i]=0;
  }
 }
 self = matrice_add_vector(self,vector_init(n,tab,&GF,2));
 for(int j=1; j<n; j++){
  for(int i=0; i<n; i++){
   if(i == self->size){
    tab[i]=1;
   } else {
    tab[i]=0;
   }
  }
  self = matrice_add_vector(self,vector_init(n,tab,&GF,2));
 }
 return matrice_transpose(self,2);
}

int matrice_compare(Matrice A, Matrice B){
 int compare = 0;
 if(A->size != B->size){
  return compare;
 }
 for(int i=0; i<A->size; i++){
   compare += vector_exists(A,B->vectors[i]);
 }
 if(compare == A->size){
  return 1;
 }
 return 0;


}

int colonne_contient_entier(Matrice m, int e, int col){

 for(int i=0; i<m->size; i++){
  if(m->vectors[i]->elements[col] == e){
   return i;
  }
 }
 return -1;

}
