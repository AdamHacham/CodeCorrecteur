#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"
#include "matrice.h"
#include "algcomb.h"
#include "alglin.h"
#include "code.h"


int traitement_buffer(char buffer[],char * function, char * variable, char ** params){
        int z =0;
        int e =0;
        int paranthese = 0;
        int egale = 0;
        int fct = 0;
        int f = 0;
        for(int i=0; i<strlen(buffer) ; i++){
         if(buffer[i] == ' ' && buffer[i+1] == '='){
          printf("\n");
          egale = 1;
          continue;
         } 
         else if(buffer[i+1] == ' ' && buffer[i] == '='){
  //         printf("function : ");
           i++;
           continue;
         } else if(buffer[i] == '(') {
           function[fct] = '\0';
//           printf("\nParams : ");
           paranthese = 1;
         } else if(egale == 1 && paranthese == 0){
           function[fct] = buffer[i];
    //       printf("%c",function[fct]);
           fct++;
         } else if(egale == 0){
           e++;
           variable[i] = buffer[i];
      //     printf("%c",variable[i]);
         } else if(paranthese == 1){

            if(buffer[i] == ','){
            z=0;
            f++;
            continue;
           } else if(buffer[i] == ')'){
            paranthese = 2;
           }else {
            params[f][z] = buffer[i];            
            z++;
           }
         }
        }
      //for(int g=0; g<3; g++){
      //      printf("%s ",params[g]);
     // }
      printf("\n");
 return f+1;
}

void commande_client(char buffer[], char *variables, char *functions, char **param, int z){
       
//         const char * ch = variables;
       if (strcmp("quit",buffer)==0){
        exit(0);
       } else if (strcmp(variables,buffer)==0){
         variables[strlen(buffer)-1] = '\0';
         if(cfileexists(strcat(variables,".code"))){
           affiche_matrice(variables);
         } else if(cfileexists(strcat(variables,".enumPoid"))){
          printf("Poids | nombre de poids\n");
           int n = get_n(variables);
           int k = get_k(variables);
          Matrice mat = recupe_matrice(variables,n,k,100000000);
          affiche_matrice(variables);
         }
       } else if (strcmp("Code",functions)==0){
        if(z != 3){
         printf("Erreur La fonction Code prend trois paramétre Code(n,k,q)\n");
        }else {
         Matrice mat = NULL;
         Vector self = NULL;
         int k = atoi(param[1]);
         int q = atoi(param[2]);
         int n = atoi(param[0]);
         Code c = nouveauCode(n,k,q);
         int * tab = malloc(sizeof tab);
         printf("Veuillez Rentrée votre  matrice génératrice \n");
         printf("mot %d : \n",0);
         for(int i = 0; i<n; i++){
          printf("elements %d : ",i);
          scanf("%i", &tab[i]);
          //printf("\n");
         }
         self = vector_init(n, tab, &GF , q);
         mat = matrice_add_vector(mat,self);         
         for(int j = 1; j<k; j++){
          printf("mot %d :  \n",j);

         for(int i = 0; i<n; i++){
          printf("elements %d : ",i);
          scanf("%i", &tab[i]);
          //printf("\n");
         }
         self = vector_init(n, tab, &GF , q);
         mat = matrice_add_vector(mat,self);
	}
         printf("\n");
         code_mat_gen(c, mat);
         ecrire_fichier(variables,c,".code");
        }
       } else if (strcmp("HammingCode",functions)==0){
        if(z != 2){
         printf("Erreur La fonction HammingCode prend deux paramétres :  HammingCode(d,k);\n");
        }else {
         Matrice matrix1 = NULL;
         Matrice matrix2 = NULL;
         int dim = atoi(param[1]);
         int q = atoi(param[0]);
         matrix1 = Hamming_parite(q,dim);
         matrix2 = Hamming_parite_forme_sys1(matrix1);
         matrix2 = Hamming_gen(matrix2,q);
         Code c = nouveauCode(matrix2->vectors[0]->size,matrix2->size,q);
         code_mat_gen(c, matrix2);
         ecrire_fichier(variables,c,".code");
        }
       } else if (strcmp("EnumPoid",functions)==0){
         if(z != 1){
          printf("Erreur La fonction EnumPoid prend un seul paramétre  EnumPoid(nomdelavariable);\n");
         } else {
           printf("Yes \n");
           char * name = strcat(param[0],".code");
           if(cfileexists(strcat(variables,".code"))){           
            printf("Cette variable exite déjà\n");
           } else {
           int n = get_n(name);
           int k = get_k(name);
           int q = get_q(name);
           Matrice mat = recupe_matrice(name,n,k,q);
           Matrice mat2 = gen_mot_code(mat,q);
	   mat2 = poids_enum(mat2,q);
           Code c = nouveauCode(n,k,q);
           code_mat_gen(c, mat2);
           ecrire_fichier(variables,c,".enumPoid");
           }
         }
       }
}

int cfileexists(const char * filename){
    /* try to open file to read */
    FILE *file;
    if (file = fopen(filename, "r")){
        fclose(file);
        return 1;
    }
    return 0;
}

