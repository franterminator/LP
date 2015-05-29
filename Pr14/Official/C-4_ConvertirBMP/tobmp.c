/*_____________________________________________________________________________

  Lee por la entrada estandar (stdin) una matriz en formato ASCII 
  correspondiente a una imagen RGB de 24 bits sin compresion de datos
  y genera el archivo tipo DIB (device-independent bitmap) que la contiene.

  Uso: tobmp OutputFileName.bmp [ < InputFileName ]
_____________________________________________________________________________*/


#include <stdlib.h>
#include <stdio.h>
#include "../C-Lib/bmp.h"

int main(int argc, char *argv[])
{
	void LeeMatrizRGB(int, int, RGB_PIXEL *);

	BITMAPFILEHEADER	bmFH;
	BITMAPINFOHEADER	bmIH;
	RGB_PIXEL         *pixM;

	int nx, ny, np;
	int rwstatus;

	if (argc != 2) {
		fprintf(stderr,
			  "\n  %s:: Error: introduzca un nombre de archivo.\n",
		        argv[0]);
		fprintf(stderr,
		        "\n  %s:: Uso  : %s OutputFileName.bmp [ < InputFileName ].\n\n",
		        argv[0], argv[0]);
		exit(1);
	}

	/* identificamos las dimensiones de la imagen RGB, */
	scanf("%d %d", &nx, &ny);

      /* inicializamos los headers, */
	SetDibHeaders(nx, ny, &bmFH, &bmIH);

	/* solicitamos memoria para almacenar la imagen, */
	np = nx * ny;
	if ((pixM = (RGB_PIXEL *) malloc(sizeof(RGB_PIXEL) * np)) == NULL) {
		fprintf(stderr,
		        "\n  %s:: Error: no hay memoria suficiente para la imagen %d x %d.\n",
		        argv[0], nx, ny);
		return 6;
	}

	/* leemos en formato ASCII la matriz RGB, */
	fprintf(stderr,
		  "\n  %s:: Importando imagen %d x %d ...\n",
	        argv[0], nx, ny); 
	LeeMatrizRGB(nx, ny, pixM);

	/* y escribimos el archivo BMP. */
	if ((rwstatus = WriteDibFile(argv[1], &bmFH, &bmIH, &pixM)) != 0) {
		fprintf(stderr,
		        "\n  %s:: Error No. %d al escribir el archivo %s.\n",
		        argv[0], rwstatus, argv[1]);
		exit(rwstatus);
	}
}



/*_____________________________________________________________________________

  Lee en formato ASCII la matriz RGB 
  de un archivo tipo DIB (device-independent bitmap)
  correspondiente a una imagen RGB de 24 bits sin compresion de datos.
______________________________________________________________________________*/

void LeeMatrizRGB(int nx, int ny, RGB_PIXEL *pixM)
{
	int ix, iy;
	int np, kp;
	int b, g, r;

	np = nx * ny;
      /* Inicializamos en negro */
	for (kp = 0; kp < np; kp++) {
		pixM[kp].blue  = (unsigned char) 0;
		pixM[kp].green = (unsigned char) 0;
		pixM[kp].red   = (unsigned char) 0;
	}

	/* Leemos Pixeles */
	while (scanf("%d %d %d %d %d", &ix, &iy, &b, &g, &r) != EOF) {
		kp = iy * nx + ix;
		pixM[kp].blue  = (unsigned char) b;
		pixM[kp].green = (unsigned char) g;
		pixM[kp].red   = (unsigned char) r;
	}
}

