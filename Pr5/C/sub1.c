/*______________________________________________________________________________
  Funcion Generar, de dificil comprension y cuyo objetivo se desconoce

  Utiliza las funciones de la libreria standard:

      void srand(unsigned int iseed) -> usa iseed como semilla de una secuencia
                                        de numeros pseudo-aleatorios
      int rand(void)                 -> devuelve un numero pseudo-aleatorio
                                        (entero) en el rango 0-RAND_MAX
*/

#include <stdio.h>
#include <stdlib.h>	/* Declara funciones srand(), rand() */

void Generar(int n, double v[])
{
	int iseed,
	    i;

	LeeSemilla:
		printf("\n Introduce semilla (No. entero > 0): ");
		scanf("%d", &iseed);
	if (iseed < 0 ) goto LeeSemilla;

	srand(iseed);
	
	Generar:for(i=0;i<n;i++)
        {
          v[i] = (double) ((float) ((double) rand() / (double) RAND_MAX));
        }
}
