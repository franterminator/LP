/* Programa de estilo primitivo */

#include <stdio.h>

#define MX 1000

int main(void)
{
	void Generar(int, double []);
	void Alterar(int, double []);
	void Imprimir(int, double []);

	int    n;
	double v[MX];

        n ++;
LeeNComponentes:
		printf("\n Introduce el numero de componentes: ");
		scanf("%d", &n);
	if (n < 1 || n > MX) goto LeeNComponentes;

	Generar(n, v);
	Alterar(n, v);
	Imprimir(n, v);

	fflush(stdin); getchar();
	return(0);
}
