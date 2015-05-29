/*______________________________________________________________________________

  Genera y escribe por la salida estandar (stdout) una matriz
  correspondiente a una imagen RGB de 24 bits del conjunto de Mandelbrot.

  El conjunto de Mandelbrot es un subconjunto del plano complejo formado
  por los puntos c = (x + y i) tales que el proceso iterativo

                             2
      z = (0 + 0 i);    z = z   + c    para   k = 1, ..., n,
       0                 k   k-1

  se mantiene acotado.
  Se puede demostrar que si

      |z | >= 2 para algun valor de k
        k

  el proceso divergera a partir de ese momento, y se dice que k es el
  numero de iteraciones de "escape" del punto c. 

  El programa estudia la region rectangular

      xc - dx < x < xc + dx,    yc - dy < y < yc + dy.

  y realiza lo siguiente:

      1) El rectangulo anterior se divide en nx por ny pixeles.

      2) Se ejecutan niter iteraciones para el punto central de cada pixel.
         El correspondiente numero de iteraciones de escape, iiter, se
         almacena en el vector kiter[nx * ny] en la forma

           kiter[iy * nx + ix] = iiter;

         Si iiter es mayor que niter se almacena un cero, lo que indica
         que el punto pertenece (posiblemente) al conjunto de Mandelbrot.

      3) Se analiza la distribucion de frecuencias del numero de
         iteraciones de escape, de forma que

           freq[iiter] = numero de pixeles para los que k <= iiter.

      4) Se asigna un color a cada pixel en funcion de la frecuencia
         del numero de iteraciones de escape, iiter, de su punto central,
         de forma que las componentes RGB del color seran
   
           b = (int) Azul (riter)
           g = (int) Verde(riter)
           r = (int) Rojo (riter)

         donde

           riter = (double) (freq[iiter] - freq[1]) /
                   (double) (freq[niter] - freq[1])  ).

         Las funciones Azul(), Verde() y Rojo() son lineales en los
         intervalos [0.0, 0.5] y [0.5, 1.0] y verifican

           Azul (0.0) = 255,    Azul (0.5) =   0,    Azul (1.0) =   0,
           Verde(0.0) =   0,    Verde(0.5) = 255,    Verde(1.0) =   0,
           Rojo (0.0) =   0,    Rojo (0.5) =   0,    Rojo (1.0) = 255.

        De esta forma se consigue una gama de colores que va
        desde el azul (que indica un numero de iteraciones de escape bajo)
        hasta el rojo (que indica un numero de iteraciones de escape alto)
        pasando por el verde.

        A los puntos del conjunto de Mandelbrot no se les asigna color, por
        lo que se representaran en el color por defecto (normalmente negro).

  Datos:

    nx, ny = dimensiones de la imagen,
    xc, yc = centro de la region rectangular que se analiza,
    dx     = semilado según el eje x de la region rectangular,
    niter  = numero maximo de iteraciones que se realizan.

______________________________________________________________________________*/


#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv)
{
	int NumIterMandel(double, double, int);

	int    nx, ny, np, ix, iy, kp;
	double xc, yc, dx, dy, x,  y;
	int    niter, iiter;
	double riter;
	int    b, g, r;

	int   *kiter,
	      *freq;

      fprintf(stderr, "\n %s:: Introduzca nx, ny, xc, yc, dx, niter: ", argv[0]);
	scanf("%d %d %le %le %le %d", &nx, &ny, &xc, &yc, &dx, &niter);
	dy = dx * ((double) ny / (double) nx);

	/* Solicitamos memoria para las frecuencias */
	freq = (int *) malloc(sizeof(int) * (1 + niter));
	if (freq == NULL) {
		fprintf(stderr, "\n %s:: Error: memoria insuficiente.\n", argv[0]); 
		exit(1);
	}

	/* Solicitamos memoria para el contador de iteraciones */
	np = nx * ny;
	kiter = (int *) malloc(sizeof(int) * np);
	if (kiter == NULL) {
		fprintf(stderr, "\n %s:: Error: memoria insuficiente.\n", argv[0]); 
		exit(2);
	}

	/* Inicializamos las frecuencias y el contador de iteraciones */
	for (iiter = 0; iiter <= niter; iiter++) {
		freq[iiter] = 0;
	}
	for (kp = 0; kp < np; kp++) {
		kiter[kp] = 0;
	}
	
	/* Calculamos el numero de iteraciones de escape para cada pixel */
	kp = 0;
	for (iy = 0; iy < ny; iy++) {
		y = yc + dy * ((double) (2 * iy + 1 - ny) / (double) (ny));
		for (ix = 0; ix < nx; ix ++) {
			x = xc + dx * ((double) (2 * ix + 1 - nx) / (double) (nx));
			iiter = NumIterMandel(x, y, niter);
			freq[iiter]++;
			kiter[kp] = iiter;
			kp++;
		}
	}

	/* Acumulamos frecuencias */
	for (iiter = 1; iiter < niter; iiter++) {
		freq[iiter + 1] += freq[iiter];
	}

	/* Y escribimos la matriz RGB */
	printf("%d %d\n", nx, ny);
	kp = 0;
	for (iy = 0; iy < ny; iy++) {
		for (ix = 0; ix < nx; ix ++) {
			iiter = kiter[kp++];
			if (iiter > 0) {
				if (freq[niter] > freq[1]) {
					riter = (double) (freq[iiter] - freq[1]) /
						  (double) (freq[niter] - freq[1]);
				} else {
					riter = 0.;
				}
				if (riter <= .5) {
					b = (int) (( 1. - 2. * riter) * 255);
					g = (int) ((      2. * riter) * 255);
					r =                               0 ;
				} else {
					b =                               0 ;
					g = (int) (( 2. - 2. * riter) * 255);
					r = (int) ((-1. + 2. * riter) * 255);
				}
				printf("%d %d %d %d %d\n", ix, iy, b, g, r);
			}
		}
	}
}


/*______________________________________________________________________________

  Dado el complejo c = (x + y i), realiza el proceso iterativo

                             2
	z = (0 + 0 i);    z = z   + c    para   k = 1, ..., n.
       0                 k   k-1

  Si |z | >= 2 para algún k, interrumpe el proceso y devuelve el valor de k.
       k

  En caso contrario devuelve 0.

  El resultado indica la relación del punto c con el Conjunto de Mandelbrot:

      0 -> posible pertenencia al conjunto,
      k -> numero de iteraciones necesarias para el escape (0 < k <= n). 

______________________________________________________________________________*/
int NumIterMandel(double x, double y, int n)
{
	double zx, zy, zxl, zyl;
	int k;

	for (zx = x, zy = y, k = 1; k <= n; k++) {
		if (zx * zx + zy * zy >= 4.) {
			return k;
		} else {
			zxl = zx; zyl = zy;
			zx = zxl * zxl - zyl * zyl + x; zy = 2. * zxl * zyl + y;
		}
	}
	return 0;
}
