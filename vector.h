#ifndef VECTOR_H__
#define VECTOR_H__

typedef struct Vector* Vector;

struct Vector {
   int size;
   int * elements;
};

int GF(int a,int b);
void affiche(Vector self);
Vector vector_init(int c, int * elem, int (*pf)(int,int), int m);
void vector_delete(Vector self);
int * vector_elements(Vector self);
void vector_set_elements(Vector self, int * elem);
Vector vector_addition(Vector A, Vector B, int (*pf)(int,int), int m);
int vector_scalaire(Vector A, Vector B);

#endif /* __VECTOR_H__ */
