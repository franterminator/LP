#include <stdio.h>

//bucle con variables enteras

int main(int argc, char *argv[])
{
	int start;
	int step = 1;
        int fin = 10;
  double x;

  for ( start = 0; start < fin; start++) {
  x = (double)start/(double)fin;
  printf("\nx: %20.9f,i: %d", x,start);
  }

  return 0;
}
