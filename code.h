#ifndef CODE_H__
#define CODE_H__

#include "matrice.h"

typedef struct Code* Code;

struct Code {
   int n;
   int k;
   int q;
   int d_min;
   Matrice mat_gen;
   Matrice mat_par;
   Matrice mots_code;
};

void ecrire_fichier(const char * name, Code c,char *  extension);
Code nouveauCode(int n, int k, int q);
void code_mat_gen(Code self, Matrice gen);
void code_mat_par(Code self, Matrice par);
void affiche_matrice(const char * name);
int get_n(const char* name);
int get_k(const char* name);
int get_q(const char* name);
#endif /* __CODE_H__ */
