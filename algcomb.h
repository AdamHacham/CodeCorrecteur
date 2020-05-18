#ifndef ALGCOMB_H__
#define ALGCOMB_H__

#include "vector.h"
#include "matrice.h"

Matrice combinaison_list(int dim, int card, int k);
int * itobase(int nbr, int base, int dim);
int est_premier(int n);
Matrice Hamming_parite(int q, int dim);
int card(int q, int dim);
Matrice matrice_combine(Matrice A, Matrice B, int k);
Matrice Hamming_parite_forme_sys(Matrice self);
Matrice Hamming_parite_forme_sys1(Matrice self);
Matrice Hamming_gen(Matrice self,int k);
Matrice gen_mot_code(Matrice self,int k);
Matrice poids_enum(Matrice self,int q);


#endif /* __ALGCOMB_H__ */
