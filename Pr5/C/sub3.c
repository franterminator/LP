/*______________________________________________________________________________
  Funcion Imprimir, de dificil comprension y cuyo objetivo se desconoce
*/

#include <stdio.h>

void Imprimir(int n, double v[])
{
	int i;

	printf("\n\n RESULTADO:\n\n");

	i = 0;
Escribir: for (i = 0; i < n; i++)
        {
          printf("    v[%5d] = %20.9f\n", i, v[i]);
	}
}
