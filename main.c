#include <stdio.h>
#include <stdlib.h>
#include "vector.h"
#include "matrice.h"
#include "algcomb.h"
#include "alglin.h"
#include "code.h"



int main(void)
{
    int tab[7] = {1,0,0,1,0,1,1};
    int tab1[7] = {0,1,0,1,1,1,0};
    int tab2[7] = {2,0,1,0,1,1,1}; 
    int tab3[5] = {0,0,2,2,6}; 
    int *tav;
    Vector self0 = NULL;
    Vector self01 = NULL;
    Vector self02 = NULL;
    Vector self03 = NULL;
    Vector self034 = NULL;
    self0 = vector_init(7,tab,&GF,61);
    self01 = vector_init(7,tab1,&GF,61);
    self02 = vector_init(7,tab2,&GF,61);
    self03 = vector_init(5,tab3,&GF,61);
    //self034 = combine_vectors(self0, self01,61);
    //affiche(self034);
    Matrice mat = NULL;
    Matrice mat1 = NULL;
    Matrice matrix = NULL;
    Matrice matrix1 = NULL;
    Matrice matrix2 = NULL;

    int * sa = recupe_size("H.code");  
    recupe_matrice("H.code",sa,2);  
    mat = matrice_add_vector(mat,self0);    
    mat = matrice_add_vector(mat,self01);    
    mat = matrice_add_vector(mat,self02);    
//    mat = matrice_add_vector(mat,self03);    
    affiche(mat->vectors[0]);
    affiche(mat->vectors[1]);
    affiche(mat->vectors[2]);
//   int ind = min_colonne_matrice(mat,0);
  printf("indice col col : %d\n", colonne_contient_entier(mat,2,0));
//    affiche(mat->vectors[3]);
   
//    mat = swap_vector(mat,1,2);    
//    affiche(mat->vectors[0]);
//    affiche(mat->vectors[1]);
//    affiche(mat->vectors[2]);
//    affiche(mat->vectors[3]);

    printf("________________________________DEBUT TRIANGULARISE_________________________\n");

    printf("matrix 1\n");
    matrix = combinaison_list(4,16,2);
    matrix1 = Hamming_parite(3,3);
    matrix2 = Hamming_parite_forme_sys1(matrix1);
    matrix2 = Hamming_gen(matrix2,3);
    matrix1 = matrice_transpose(matrix1,3);
    printf("taille vecteur : %d\n",matrix1->vectors[0]->size);
    for(int i=0; i<matrix1->size;i++){
     affiche(matrix1->vectors[i]);
//     printf("est_null : %d\n",vector_null(mat1->vectors[i]));
    }
    

//    mat1 = combinaison_list(3,27,3);
//    matrix2 = matrice_transpose(matrix2,3);
    

    printf("mat\n");
    for(int i=0; i<matrix2->size;i++){
     affiche(matrix2->vectors[i]);
//     printf("est_null : %d\n",vector_null(mat1->vectors[i]));
    }

//   Code c = nouveauCode(7,4,2);
//   printf("all\n");
//   code_mat_gen(c, matrix2);
//   ecrire_fichier("hamming",c);
//   affiche_matrice("hamming");
//    matrix1 = matrice_multiplication(matrix, matrix1, 2);
      //matrix1 = 
      matrix2 = gen_mot_code(matrix2, 3);
      matrix1 = gen_mot_code(matrix1, 3);
   // int e = matrice_compare(matrix1, matrix2);
   // printf("e = %d\n",e);

    printf("matrix 1\n");
    for(int i=0; i<matrix1->size;i++){
     affiche(matrix1->vectors[i]);
//     printf("est_null : %d\n",vector_null(mat1->vectors[i]));
    }

    printf("matrix 2\n");
    printf("matrix taille : %d\n",matrix2->size);
    matrix2 = poids_enum(matrix2,5);
   
    for(int i=0; i<matrix2->size;i++){
     affiche(matrix2->vectors[i]);
//     printf("est_null : %d\n",vector_null(mat1->vectors[i]));
    }


    printf("indice vecteur : %d\n",min_colonne_matrice(mat,0));
    printf("colonne null  : %d\n",colonne_null(mat,0));

    vector_delete(self0);
    vector_delete(self01);
    vector_delete(self02);
    vector_delete(self03);
  
    return 0;
}
