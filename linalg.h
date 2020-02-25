#ifndef __LINALG_H__
#define __LINALG_H__

//#define NAME_MAX_LEN 32

typedef struct Matrice Matrice;

int GF(int a,int b);
void affiche(Matrice *self);
Matrice* matrice_init(int l, int c, int * elem, int (*pf)(int,int), int m);
void matrice_delete(Matrice *self);
int * matrice_elements(Matrice *self);
void matrice_set_elements(Matrice *self, int * elem);
Matrice * matrice_transposee(Matrice *self,int n);
#endif /* __LINALG_H__ */

