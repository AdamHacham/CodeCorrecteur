/* ---------------------------------------------------------- */
/*                                                            */
/* Programme : gauss.c                                        */
/* Objectif  : Résolution d'un système linéaire du type :     */
/*                                                            */
/*                       A x =  b                             */
/*                                                            */
/*             par la méthode d'élimination de Gauss.         */
/* ---------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float * * malloc2 ( int rows , int cols ) ;
void saisie_mat(float **A ,int n) ;
void saisie_vect(float *b ,int n) ;
void affich_systeme(float **A ,float *b ,int n) ;
void gauss(float **A, float *b, float *x, int n) ;
void affich_sol(float *x, int n) ;

main()
{
      int n ;        // taille du système
      int i, j ;
      float * * A ;  // matrice A
      float * b ;    // vecteur b
      float * x ;    // vecteur des inconnues x
      
      /* Saisie de la taille du système */
      printf("\nDimension du systeme : ") ;
      scanf("%d", &n) ;
      printf("\n") ;
      
      /* Allocation de mémoire pour A, b et x */
      A = malloc2(n,n) ;
      b = (float *) malloc (sizeof (float *) * n) ;
      x = (float *) malloc (sizeof (float *) * n) ;
      
      /* Saisie de la matrice A et du vecteur b */
      saisie_mat(A,n) ;
      saisie_vect(b,n) ;
      
      /* Affichage du système initial */
      affich_systeme(A,b,n) ;
      
      /* Résolution du système par la méthode d'élimination de Gauss */
      gauss(A,b,x,n) ;
      
      /* Affichage du système réduit */
      affich_systeme(A,b,n) ;
      
      /* Affichage de la solution du système */
      affich_sol(x,n) ;
      
      free(A) ;
      free(b) ;
      
      exit( EXIT_SUCCESS ) ;
}

float * * malloc2 ( int rows , int cols ) 
{
    float * * ptr = ( float * * ) malloc ( sizeof ( float * ) * rows + sizeof ( float ) * cols * rows ) ;
    float *   dat = ( float *   ) ( ptr + rows ) ;
    int i ;
    if ( ptr == NULL ) exit( EXIT_FAILURE ) ;
    for ( i = 0 ; i < rows ; ++ i , dat += cols ) ptr [ i ] = dat ;
    return ptr ;
}

/* Saisie des éléments de la matrice A */
void saisie_mat(float **A ,int n)
{ 
     int i , j ;
     printf(" ===>Saisie de la matrice : \n\n\n");
     
     for(i = 0 ; i < n ; i++)
     {
        for( j = 0 ; j < n ; j++)
        {
           printf("  A[%d][%d] : ",i+1,j+1);
           scanf("%f",&A[i][j]);
        }
     printf("\n");
     }
}

/* Saisie des éléments de la matrice B */
void saisie_vect(float *b ,int n)
{ 
     int i ;
     printf(" ===>Saisie du vecteur : \n\n\n");
     
     for(i = 0 ; i < n ; i++)
     {
        printf("  b[%d] : ",i+1);
        scanf("%f",&b[i]);
        printf("\n");
     }
}

/* Affichage du système */
void affich_systeme(float **A ,float *b ,int n)
{
	int i , j ;
	printf(" ===>Affichage du systeme : \n\n\n");
	
	for(i = 0 ; i < n ; i++)
	{
		printf("  (");
		for(j = 0 ; j < n ; j++)
		{
			printf("  %.3f  ",A[i][j]);
		}
		printf(" )    (X%d)   =",i+1);
		printf("\t%.3f",b[i]);
		printf("\n\n");
	}
}

/* Affichage de la solution du système */
void affich_sol(float *x, int n)
{
    int i ;
	printf(" ===>Affichage de la solution : \n\n\n");
	
	for(i = 0 ; i < n ; i++)
	{
        printf("(X%d)   =",i+1);
		printf("\t%.6f",x[i]);
		printf("\n\n");
	}
}

/* Méthode d'élimination de Gauss */
void gauss(float **A, float *b, float *x, int n)
{
     int i, j, k ;
     int imin ;
     float p ;
     float sum, valmin, tump1, tump2 ;
     
     for(k = 0 ; k < n-1 ; k++)
     {
        /* Dans un premier temps, on cherche l'élément minimum (non */
        /* nul) en valeur absolue dans la colonne k et d'indice i   */
        /* supérieur ou égal à k.                                   */
        
        valmin = A[k][k] ; imin = k ;
        for(i = k+1 ; i < n ; i++)
        {
           if (valmin != 0)
           {
              if (abs(A[i][k]) < abs(valmin) && A[i][k] != 0)
              {
                 valmin = A[i][k] ;
                 imin = i ;
              }
           }
           else 
           {
                 valmin = A[i][k] ;
                 imin = i ;
           }     
        }
        
        /* Si l'élément minimum est nul, on peut en déduire */
        /* que la matrice est singulière. Le pogramme est   */
        /* alors interrompu.                                */
        
        if (valmin == 0.)
        {
           printf("\n\n\nAttention! Matrice singuliere!\n\n\n") ;
           exit( EXIT_FAILURE ) ;
        }
        
        /* Si la matrice n'est pas singulière, on inverse    */
        /* les éléments de la ligne imax avec les éléments   */
        /* de la ligne k. On fait de même avec le vecteur b. */
        
        for(j = 0 ; j < n ; j++)
        {
           tump1 = A[imin][j] ;
           A[imin][j] = A[k][j] ;
           A[k][j] = tump1 ;
        }
        
        tump2 = b[imin] ;
        b[imin] = b[k] ;
        b[k] = tump2 ;
        
        
        /* On procède à la réduction de la matrice par la */
        /* méthode d'élimination de Gauss. */
        
        for(i = k+1 ; i < n ; i++)
        {
           p = A[i][k]/A[k][k] ;
           
           for(j = 0 ; j < n ; j++)
           {
              A[i][j] = A[i][j] - p*A[k][j] ;
           }
           
           b[i] = b[i] - p*b[k] ; 
        }
     }   
     
     /* On vérifie que la matrice n'est toujours pas singulière. */
     /* Si c'est le cas, on interrompt le programme. */
     
     if (A[n-1][n-1] == 0)
     {
        printf("\n\n\nAttention! Matrice singuliere!\n\n\n") ;
        exit( EXIT_FAILURE ) ; 
     }
     
     /* Une fois le système réduit, on obtient une matrice triangulaire */
     /* supérieure et la résolution du système se fait très simplement. */
     
     x[n-1] = b[n-1]/A[n-1][n-1] ;
     
     for(i = n-2 ; i > -1 ; i--)
     {
           sum = 0 ;
           
           for(j = n-1 ; j > i ; j--)
           {
              sum = sum + A[i][j]*x[j] ;
           }
           x[i] = (b[i] - sum)/A[i][i] ;
     }
}
