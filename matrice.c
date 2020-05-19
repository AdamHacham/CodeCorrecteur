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
 for(int i = 0; i<self->size; i++){
  vector_delete(self->vectors[i]);  
 }
 free(self);
}

int * recupe_size(const char * name){
   FILE* fichier = NULL;
    //int age = 0;
    int i=0;
    int j=0;
    int e = 0;
    int size=0;
    int *tab = malloc(sizeof tab);;
    int caractereActuel = 0;
    fichier = fopen(name, "r");
    if (fichier != NULL)
    {
     do
        {
            caractereActuel = fgetc(fichier);
            char c = caractereActuel;
//            fscanf(fichier,"%c", c);
            if(i < 8){
             i++;
             continue;
            } else if( c == ' '){
             j++;
           
             continue;
            } else if (c == '\n'){
             //printf("\n");
             size = j;
             j = 0;
             e++;
             continue;
            }else {

            }
                        
        } while (caractereActuel != EOF);
      tab[0] = size;
      tab[1] = e;
      printf("n : %d\nk : %d\n",tab[0],tab[1]);
    }
      return tab;

}


Matrice recupe_matrice(const char * name, int n, int k, int q){
    FILE* fichier = NULL;
    int i=0;
    int j=0;
    int x =0;
    int e = 0;
    char **param = malloc((n*k) * sizeof (char *));
 
     for(int w = 0; w<(n*k); w++){
      param[w] = malloc(2*sizeof **param);
     }
    int caractereActuel = 0;
    fichier = fopen(name, "r");
    if (fichier != NULL)
    {
     do
        {
            caractereActuel = fgetc(fichier);
//            char c = caractereActuel;
          if(j >= n*k){
           break;
          }else if(i >= 4){
              //printf("%c",caractereActuel);    
//              printf("\n");
             if((caractereActuel != ' ') && (caractereActuel != '\n')){
    //          printf("%d\t",j);    
 	      param[j][x] = caractereActuel;
  //            printf("%c\n",caractereActuel);
              x++;
             } else if (caractereActuel == '\n'){
      //        printf("\n");
//              break;
              continue;
             } else {
	      param[j][x] = '\0';              
              x=0;
              j++;
	     } 
         } else if (caractereActuel == '\n' && i < 4){
           i++;
         } 
  //      printf("\n");
        } while (caractereActuel != EOF);
//printf("malloc\n");     
    int *tab = malloc((n+1)*sizeof (int));
    int e = 0;
    Matrice mat = NULL;
    for(int m =0; m<n;m++){
//     printf("%s",param[m]);  
    tab[m] = atoi(param[e]);
      e++;
    }      
    Vector v = vector_init(n,tab,&GF,q);
    mat = matrice_add_vector(mat,v);
//    affiche(v);
    for(int a = 1; a<k ;a++){
    for(int b = 0 ; b<n;b++){
      tab[b] = atoi(param[e]);
      e++;
    }

    Vector v1 = vector_init(n,tab,&GF,q);
         mat = matrice_add_vector(mat,v1);
  //  affiche(v1);
    }      
    return mat;
    }
}
