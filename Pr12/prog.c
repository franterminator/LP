#include <stdio.h>
#include <stdlib.h>
/*______________________________________________________________________________
______________________________________________________________________________*/

int main(void)
{
	void LeerVector(int, char *, double *);
	double ProductoEscalar(int, double *, double *);
	void FError(FILE* , char *, int);

	int    n;
	double pe;

	double *v1;
        double *v2;

	LeeNComponentes:
		printf("\n Introduce el numero de componentes: ");
		scanf("%d", &n);
	if (n < 1) goto LeeNComponentes;

        // Memory allocation
        v1 = (double *)malloc(sizeof(double) * n);
        if(v1==NULL) FError(stderr,"problema al crear el puntero 1",2);
        v2 = (double *)malloc(sizeof(double) * n);
        if(v2==NULL) FError(stderr,"problema al crear el puntero 2",2);
        
	printf("\n Introduzca vector v1[]:\n\n");
	LeerVector(n, "v1", v1);

	printf("\n Introduzca vector v2[]:\n\n");
	LeerVector(n, "v2", v2);

	pe = ProductoEscalar(n, v1, v2);

	printf("\n Producto escalar de v1[] * v2[] = %25.15le\n\n", pe);  

	fflush(stdin); getchar();
	exit(0);
}


/*________________________________________________________________LeerVector__*/

void LeerVector(int n, char *nombre, double *v)
{
	int i;

	for (i = 0; i < n; i++) {
		printf("       %s [%6d] = ", nombre, i);
		scanf("%le", &v[i]);
	}
}

/*_____________________________________________________________ProductoEscalar*/
double ProductoEscalar(int n, double *v1, double *v2){
    double pe;
    
    for(; n>=0; n--) 
        pe += v1[n]*v2[n];
    return pe;
}

/*____________________________________________________________________FError__*/

void FError(FILE* fperr, char *error, int ierr)
{
	fprintf(fperr, "\n prueba:: Error: %s\n", error);

	fprintf(stderr, "\n Fin de Ejecucion. Oprima RETURN para salir.");
	fflush(stdin); getchar();
	exit(ierr);
}
