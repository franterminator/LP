//bucle con variables reales
#include <stdio.h>

int main(int argc, char *argv[])
{
	double start;
	double step = 0.1;
	double fin = 1;

	for (start = 0; start <= fin; start += step){
	printf("\nx: %24.18f", start);
	}
  return 0;
}
