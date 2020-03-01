#ifndef MATRICE_H__
#define MATRICE_H__

#include "vector.h"

typedef struct Matrice* Matrice;

struct Matrice {
 int size;
 Vector *vectors;
};

Matrice matrice_add_vector(Matrice mat, Vector vector);
Matrice matrice_transpose(Matrice self, int k);
void matrice_delete(Matrice self);
Vector vector_colonne(int c, Matrice self, int k);
Matrice matrice_multiplication(Matrice A, Matrice B, int k);

#endif /* MATRICE_H__ */