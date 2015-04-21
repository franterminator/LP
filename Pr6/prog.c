#include <stdio.h>
#include <stdlib.h>

#define PI 3.14159265358979324

//este programa calcula el valor de Pi mediante un metodo de Monte-Carlo
int main(int argc, char *argv[])
{
  int n;                   //numero de iteraciones
  unsigned int seed;       //semilla para cambiar el nº aleatorio generado

  while(0 < 10){
    printf("\n Introduce un numero de iteraciones: ");
    scanf("%d", &n);
    if(n > 0) break;
  }
  
  while(0 < 10){
    printf("\n Introduce la semilla: ");
    scanf("%d", &seed);
    if(seed > 0) break;
  }

  //inicializamos la generación de Nº aleatorios
  srand(seed);

  //simulación
  int nf=0;
  int i;
  for (i = 0; i < n; i++) {
    double x = (double) rand()/RAND_MAX;
    double y = (double) rand()/RAND_MAX;
    if(x*x+y*y < 1.)
      nf++;
  }

  double pi_aprox = 4. * (double) nf / (double)n;
  double error = (pi_aprox - PI)/PI;

  //imprimimos los resultados
  printf("\n RESULTADOS: \
          \n   n  = %02d ; nf = %02d  \
          \n   PI (aprox)     = %20.6f\
          \n   PI (exacto)    = %20.6f\
          \n   error relativo = %8.4f",
         n,nf,pi_aprox,PI,error);

  //para cerrar el programa el usuario debera pulsar una tecla
  fflush(stdin); getchar();
  
  return 0;
}
