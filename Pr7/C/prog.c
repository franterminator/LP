/*
PROGRAMA PARA DERIVAR UN POLINOMIO

   1. El usuario introduce los datos del polinomio, esto se hace en el metodo leerCoeficientes()
   Polinomio que sigue esta forma:
   P_n(x) = a_0 + a_1*x + a_2*x^2 + a_3*x^3 + ... + a_n*x^n
   Donde n es el grado del polinomio.
   
   2. Luego el usuario introduce el punto z.
   Se realiza el cambio de base a la base (x-z). Para ello se divide el polinomio por (x-z).
   Esto se realiza en el metodo divisionSintetica().
   
   3. Se calcula las derivadas
            (i       |
           d P_n(x)  |
   c (i) = --------- |
              (i     |
           d x       | x = z
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX 100

int main (int argc, char *argv[]) {
    /*prototype*/
    void leerCoeficientes(int, double *);
    void divisionSintetica(int, double, double *, double *);
    void calcularDerivadas(int, double *, double *);
    void escribirResultados(int, double, double *, double *, double *);
    /*variables*/
    int n; //polinomial's grade

    do{
        printf("\n Introduce el grado del polinomio (max=100) -> n = ");
        scanf("%d", &n);
    } while (n <= 0 || n >= 100);
    double a[n];
    double b[n];
    double c[n];

    double z;
    printf("\n Introduce el punto de calculo -> z = ");
    scanf("%lf", &z);

    /*call methods*/
    leerCoeficientes(n,a);
    divisionSintetica(n,z,a,b);
    calcularDerivadas(n,b,c);
    escribirResultados(n,z,a,b,c);
    
    /*wait for user keyboard*/
    fflush(stdin); getchar();
    
    return 0;
} //end of method main
