#ifndef ALGLIN_H__
#define ALGLIN_H__

#include "vector.h"
#include "matrice.h"

Matrice triangularise_mat(Matrice self, int k);
Matrice simplification_mat(Matrice self,int k);
int vector_exists(Matrice self, Vector v);
int vector_null(Vector v);
int min_colonne_matrice(Matrice A, int indice_colonne);
int colonne_null(Matrice A, int indice_colonne);
Matrice swap_vector(Matrice A, int i, int j);
int max_colonne_matrice(Matrice A, int indice_colonne);
Matrice matrice_identite(int n);
int matrice_compare(Matrice A, Matrice B);
int colonne_contient_entier(Matrice m, int e, int col);


#endif /* __ALGLIN_H__ */
