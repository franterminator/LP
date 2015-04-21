#include <stdio.h>
#include <stdlib.h>
/*metodo para dividir el polinomio por (x-z)*/
void escribirResultados(int n, double z, double a[], double b[] ,double c[]){
	printf("\n RESULTADOS");
	
	printf("\n Grado del polinomio -> n = %5d",n);
	printf("\n Punto de calculo -> z = %20.9f",z);
	
	printf("\n Coeficiente en la base {1,x,...,x^n}:");
	int i;
	for( i = 0; i <= n; i++){
	printf("\n\ta[%d] = %20.9f",i,a[i]);
	}
	
	printf("\n Coeficiente en la base {1,(x-z),...,(x-z)^n}:");
	for( i = 0; i <= n; i++){
	printf("\n\ta[%d] = %20.9f",i,b[i]);
	}
	
	printf("\n Funcion y derivadas en el punto x = z:");
	for( i = 0; i <= n; i++){
	printf("\n\ta[%d] = %20.9f",i,c[i]);
	}
	
	return ;
}