#include <stdio.h>
#include <stdlib.h>
/*metodo para leer de la pantalla los coeficientes introducidos por el usuario*/
void leerCoeficientes(int n, double v[]){
	
	printf("\n Introduzca los coeficientes del polinomio: ");
	int i;
	for(i=0; i <= n; i++){
		printf("\n\t a(%d) = ",i);
		scanf("%lf",&v[i]);
	}
	return ;

}//end of method leerCoeficientes