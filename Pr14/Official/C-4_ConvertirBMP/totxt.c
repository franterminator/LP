/*_____________________________________________________________________________

  Escribe en la salida estandar (stdout) la matriz RGB en formato ASCII 
  correspondiente a una imagen RGB de 24 bits sin compresion de datos
  contenida en un archivo tipo DIB (device-independent bitmap).

  Uso: totxt InputFileName.bmp [ > OutputFileName.txt ]
_____________________________________________________________________________*/


#include <stdlib.h>
#include <stdio.h>
#include "../C-Lib/bmp.h"

int main(int argc, char *argv[])
{
	void EscribeMatrizRGB(int, int, RGB_PIXEL *);

	BITMAPFILEHEADER	bmFH;
	BITMAPINFOHEADER	bmIH;
	RGB_PIXEL         *pixM;

	int nx, ny;
	int rwstatus;

	if (argc != 2) {
		fprintf(stderr,
		        "\n  %s:: Error: introduzca un nombre de archivo.\n",
		        argv[0]);
		fprintf(stderr,
		        "\n  %s:: Uso  : %s InputFileName.bmp [ > OutputFileName.txt ].\n\n",
		        argv[0], argv[0]);
		exit(1);
	}

	/* Leemos el archivo BMP, */
	if ((rwstatus = ReadDibFile(argv[1], &bmFH, &bmIH, &pixM)) != 0) {
		fprintf(stderr,
		        "\n  %s:: Error No. %d al leer el archivo %s.\n",
		        argv[0], rwstatus, argv[1]);
		exit(rwstatus);
	}

	/* identificamos las dimensiones de la imagen RGB, */
	nx = bmIH.biWidth;
	ny = bmIH.biHeight;
	printf("%d %d\n", nx, ny);

	/* y escribimos en formato ASCII la matriz RGB. */
	fprintf(stderr,
		  "\n  %s:: Exportando imagen %d x %d ...\n",
	        argv[0], nx, ny);
	EscribeMatrizRGB(nx, ny, pixM);
}



/*_____________________________________________________________________________

  Escribe en formato ASCII la matriz RGB 
  de un archivo tipo DIB (device-independent bitmap)
  correspondiente a una imagen RGB de 24 bits sin compresion de datos.

  Se usa la notacion abreviada:
                                ep->m  <-> (*ep).m
______________________________________________________________________________*/

void EscribeMatrizRGB(int nx, int ny, RGB_PIXEL *pixM)
{
	int ix, iy;

	/* Pixeles */
	for (iy  =  0; iy < ny; iy++) {
		for (ix  =  0; ix < nx; ix++) {
			printf("%d %d %d %d %d\n",
				 ix, iy, pixM->blue, pixM->green, pixM->red);
			pixM++;
		}
	}
}
