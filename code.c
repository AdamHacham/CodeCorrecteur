#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "vector.h"
#include "code.h"

#include "matrice.h"



Code nouveauCode(int n, int k, int q){
  
  Code c = NULL;
  c = malloc(sizeof c);  
  c->n = n;
  c->k = k;
  c->q = q;
  c->d_min = 3;
  c->mat_gen = NULL;
  c->mat_par = NULL;
  return c;
}

void code_mat_gen(Code self, Matrice gen){
 self->mat_gen = gen;
}
void code_mat_par(Code self, Matrice par){
 self->mat_par = par;
}

int get_n(const char* name){



    FILE* fichier = NULL;
    int caractereActuel = 0;
    int i = 0;
    int e = 0;
    int res = 0;
    fichier = fopen(name, "r");
    char * ch = malloc(3 * sizeof (char));
    if (fichier != NULL)
    {
     do
        {    
             caractereActuel = fgetc(fichier);
             if(i == 0){
             ch[e] = caractereActuel;
             e++;
             } else if (caractereActuel == '\n'){
               i++;
             }
        } while (caractereActuel != EOF);
             res = atoi(ch);
    }
 return res;

}

int get_k(const char* name){
    FILE* fichier = NULL;
    int caractereActuel = 0;
    int i = 0;
    int e = 0;
    int res = 0;
    fichier = fopen(name, "r");
    char * ch = malloc(3*sizeof (char));
    if (fichier != NULL)
    {
     do
        {
             caractereActuel = fgetc(fichier);
             if(i == 1){
             ch[e] = caractereActuel;
             e++;
             } else if(caractereActuel == '\n'){
               i++;
             }
        } while (caractereActuel != EOF);
     res = atoi(ch);
    }
 return res;
}

int get_q(const char* name){

 FILE* fichier = NULL;
    int caractereActuel = 0;
    int i = 0;
    int e = 0;
    int res = 0;
    fichier = fopen(name, "r");
    char * ch = malloc(3*sizeof (char));
    if (fichier != NULL)
    {
     do
        {
             caractereActuel = fgetc(fichier);
             if(i == 2){
             ch[e] = caractereActuel;
             e++;
             } else if(caractereActuel == '\n'){
               i++;
             }
        } while (caractereActuel != EOF);
     res = atoi(ch);
    }
 return res;

}

void ecrire_fichier(const char* name, Code c, char * extension){

    FILE* fichier = NULL;
    fichier = fopen(strcat(name,extension), "w");
    if (fichier != NULL)
    {
        fprintf(fichier, "%d\n", c->n);
        fprintf(fichier, "%d\n", c->k);
        fprintf(fichier, "%d\n", c->q);
        fprintf(fichier, "%d\n", c->d_min);
        for(int i=0; i<c->mat_gen->size; i++){
         for(int j=0; j<c->mat_gen->vectors[0]->size; j++){
          fprintf(fichier, "%d ", c->mat_gen->vectors[i]->elements[j]);
         }
         fputs("\n", fichier);
        }
        fclose(fichier);
    }
}

void affiche_matrice(const char * name){
   FILE* fichier = NULL;
    //int age = 0;
    int i=0;
    int caractereActuel = 0;
    fichier = fopen(name, "r");
    if (fichier != NULL)
    {
     do
        {
             caractereActuel = fgetc(fichier);
             if(i >= 4){
               printf("%c ", caractereActuel); // On l'affiche
             } else if (caractereActuel == '\n'){
               i++;
             }
        } while (caractereActuel != EOF);
      printf("\n");
    }
}
