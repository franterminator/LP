#include <stdio.h>
#include <stdlib.h>
/*metodo para dividir el polinomio por (x-z)*/
void calcularDerivadas(int n, double a[], double b[]){
	int i;
	for(i = 0; i <= n; i++)
		b[i] = a[i];
		
	double fact = 1.;
	for(i = 2; i <= n; i++){
		fact *= (double)i;
		b[i] *= fact;
	}
	
		
	return ;
}