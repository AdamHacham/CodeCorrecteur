#include <stdio.h>  
#include <stdlib.h> 
#include "vector.h"
#include "matrice.h"
#include "algcomb.h"
#include "alglin.h"


int est_premier(int n) {
    int i, flag = 0;
    for (i = 2; i <= n / 2; ++i) {
        if (n % i == 0) {
            flag = 1;
            break;
        }
    }

    if (n == 1) {
      return 0;
    }
    else {
        if (flag == 0)
           return 1;
        else
           return 0;
    }

}

Matrice combinaison_list(int dim, int card, int k)
{
 Matrice mat = NULL;
 for(int i=0; i<card ;i++)
 {
  int * tab = itobase(i,k,dim);
  Vector self = vector_init(dim,tab,&GF,k);
//  affiche(self);
//  printf("i : %d\n",i);
  mat = matrice_add_vector(mat,self);  
 }
 return mat;
}

Matrice Hamming_parite(int q, int dim){
 int cardinal = card(q,dim);
 Matrice self = combinaison_list(dim,cardinal,q);
 Matrice mat = NULL;
 mat = matrice_add_vector(mat,self->vectors[1]);
// printf("Sal\n");
 for(int i=1; i<cardinal ;i++)
 {
  int boul = 0;
  for(int j = 0; j<mat->size; j++){
   boul += vector_compare_multiple(self->vectors[i], mat->vectors[j],q);
  }
  if(boul == mat->size){
   mat = matrice_add_vector(mat,self->vectors[i]);
  }
 }
 return mat;
}


Matrice Hamming_parite_forme_sys1(Matrice self){
 int indice ;
 Matrice mat = NULL;
 Matrice mat1 = NULL;
 mat1 = matrice_identite(self->vectors[0]->size);
  for(int i = 0 ; i< self->size; i++){
  if(vector_exists(mat1,self->vectors[i]) == 0){
   indice = i;
   break;
  }
 }
 mat = matrice_add_vector(mat,self->vectors[indice]);

 for(int i = 0 ; i< self->size; i++){
 if((vector_exists(mat1,self->vectors[i]) == 0) && (vector_exists(mat,self->vectors[i]) == 0)){
  mat = matrice_add_vector(mat,self->vectors[i]);
 }
 }
 
 for(int i = 0 ; i< mat1->size; i++){
  mat = matrice_add_vector(mat,mat1->vectors[i]);
 }
 return mat;
}

Matrice Hamming_gen(Matrice self,int k){
 int indice;
 Matrice mat = NULL;
 Matrice mat1 = NULL;
 mat1 = matrice_identite(self->vectors[0]->size);
 for(int i = 0 ; i< self->size; i++){
  if(vector_exists(mat1,self->vectors[i]) == 0){
   indice = i;
   break;
  }
 }
 mat = matrice_add_vector(mat,self->vectors[indice]);

 for(int i = 0 ; i< self->size; i++){
 if((vector_exists(mat1,self->vectors[i]) == 0) && (vector_exists(mat,self->vectors[i]) == 0)){
  mat = matrice_add_vector(mat,self->vectors[i]);
 }
 }
 Matrice mat2 = NULL;
 mat2 = matrice_identite(mat->size);
 Matrice res = NULL;
 res = matrice_combine(mat2,mat,k);
 return res;
}


Matrice Hamming_parite_forme_sys(Matrice self){
 Matrice mat = NULL;
 mat = matrice_add_vector(mat,self->vectors[self->size-1]);
 
 for(int i = self->size-2 ; i<= 0; i++){
 mat = matrice_add_vector(mat,self->vectors[i]);
 }
 return mat;
}

//Matrice matrice_A_forme_syst(Matrice self){
 


//}

Matrice matrice_combine(Matrice A, Matrice B, int k){
 Matrice self = NULL;
 if(A->size != B->size){
  printf("Dimension des deux matrices differents\n");
  return NULL;
 }
 for(int i =0; i<A->size; i++){
  Vector v = combine_vectors(A->vectors[i],B->vectors[i],k);
  self = matrice_add_vector(self,v);
 }
 return self;
}
int card(int q, int dim){
 int card = 1;
 for(int i=0; i<dim; i++){
  card *= q;
 }
 return card;
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

Matrice gen_mot_code(Matrice self,int k){
 Matrice matrix = NULL;
 matrix = combinaison_list(self->size,card(k,self->size),k);
 
 Matrice mat = NULL;
   Vector v1 = vector_multiplication_scalaire(self->vectors[0],matrix->vectors[0]->elements[0],&GF,k);
  for(int j=1 ; j<matrix->vectors[0]->size; j++){
    v1 = vector_addition(v1,vector_multiplication_scalaire(self->vectors[j],matrix->vectors[0]->elements[j],&GF,k),&GF,k);
  }

 mat = matrice_add_vector(mat,v1);
 
 for(int i=1; i< matrix->size; i++){
  Vector v = NULL;
  Vector v1 = vector_multiplication_scalaire(self->vectors[0],matrix->vectors[i]->elements[0],&GF,k);
  for(int j=1 ; j<matrix->vectors[0]->size; j++){
    v1 = vector_addition(v1,vector_multiplication_scalaire(self->vectors[j],matrix->vectors[i]->elements[j],&GF,k),&GF,k);
  }
 mat = matrice_add_vector(mat,v1);
 }

 return mat; 


}

Matrice poids_enum(Matrice self,int q){

 Matrice mat = NULL;
 Vector self1 = NULL;
 int d = vector_poid(self->vectors[0]);
 int compteur = 0;
 compteur += 1;
 int tab[2] = {d,compteur};
 self1 = vector_init(2,tab,&GF,1000000);
 mat = matrice_add_vector(mat,self1);
 for(int i = 1; i<self->size; i++){
   int p = vector_poid(self->vectors[i]);
   int ex = colonne_contient_entier(mat, p, 0);
   if(ex != -1){
     mat->vectors[ex]->elements[1]++;
   } else {
    tab[0] = p;
    tab[1] = 1;
    Vector v = vector_init(2,tab,&GF,1000000);
    mat = matrice_add_vector(mat,v);

   }
  }

return mat;
}
