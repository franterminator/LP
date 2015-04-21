#include <stdio.h>
#include <stdlib.h>
/*metodo para dividir el polinomio por (x-z)*/
void divisionSintetica(int n, double z, double a[], double b[]){
	int i;
	for(i = 0; i <= n; i++)
		b[i] = a[i];
	
	int k;
	for(k = n; k >= 1; k--){
		for(i = n-1; i >= n-k; i--)
			b[i] += b[i+1]*z;
	}

	return ;
}
