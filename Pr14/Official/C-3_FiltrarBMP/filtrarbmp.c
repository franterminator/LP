/*_____________________________________________________________________________

  Filtra (descompone en imagenes monocromas 'B', 'G', 'R') el contenido
  de un archivo tipo DIB (device-independent bitmap)
  correspondiente a una imagen RGB de 24 bits sin compresion de datos.

  Uso: filtrarbmp archivo.bmp archivoB.bmp archivoG.bmp archivoR.bmp
_____________________________________________________________________________*/


#include <stdlib.h>
#include <stdio.h>
#include "../C-Lib/bmp.h"


int main(int argc, char *argv[])
{
	void FiltrarRGBPixels(char, int, int, RGB_PIXEL *, RGB_PIXEL *);

	BITMAPFILEHEADER	bmFH;
	BITMAPINFOHEADER	bmIH;
	RGB_PIXEL         *pixM, *pixM2;

	int nx, ny, np;
	int rwstatus;

	if (argc != 5) {
		fprintf(stderr,
			  "\n  %s:: Error: introduzca cuatro nombres de archivo.\n",
		        argv[0]);
		fprintf(stderr,
		        "\n  %s:: Uso  : %s archivo.bmp archivoB.bmp archivoG.bmp archivoR.bmp.\n\n",
		        argv[0], argv[0]);
		exit(1);
	}

	/* Leemos el archivo, */
	if ((rwstatus = ReadDibFile(argv[1], &bmFH, &bmIH, &pixM)) != 0) {
		fprintf(stderr,
		        "\n  %s:: Error No. %d al leer el archivo %s.\n",
		        argv[0], rwstatus, argv[1]);
		exit(rwstatus);
	}

	/* identificamos las dimensiones de la imagen RGB, */
	nx = bmIH.biWidth;
	ny = bmIH.biHeight;


	/* solicitamos memoria para almacenar la imagen filtrada,*/
	np = nx * ny;
	if ((pixM2 = (RGB_PIXEL *) malloc(sizeof(RGB_PIXEL) * np)) == NULL) {
		fprintf(stderr,
		       "\n  %s:: Error: no hay memoria suficiente para la imagen %d x %d.\n",
		       argv[0], nx, ny);
		return 6;
	}

	/* filtramos la imagen (blue) */
	fprintf(stderr,
	        "\n\n  Procesando componente azul de la imagen %d x %d ...\n",
	        nx, ny);        
	FiltrarRGBPixels('B', nx, ny, pixM, pixM2);

	/* y escribimos un nuevo archivo con la imagen modificada. */
	if ((rwstatus = WriteDibFile(argv[2], &bmFH, &bmIH, &pixM2)) != 0) {
		fprintf(stderr,
		        "\n  %s:: Error No. %d al escribir el archivo %s.\n", 
		        argv[0], rwstatus, argv[2]);
		exit(rwstatus);
	}

	/* filtramos la imagen (green) */
	fprintf(stderr,
	        "\n\n  Procesando componente verde de la imagen %d x %d ...\n",
	        nx, ny);       
	FiltrarRGBPixels('G', nx, ny, pixM, pixM2);

	/* y escribimos un nuevo archivo con la imagen modificada. */
	if ((rwstatus = WriteDibFile(argv[3], &bmFH, &bmIH, &pixM2)) != 0) {
		fprintf(stderr,
		        "\n  %s:: Error No. %d al escribir el archivo %s.\n",
		        argv[0], rwstatus, argv[3]);
		exit(rwstatus);
	}

	/* filtramos la imagen (red) */
	fprintf(stderr,
	        "\n\n  Procesando componente roja de la imagen %d x %d ...\n",
	        nx, ny);
	FiltrarRGBPixels('R', nx, ny, pixM, pixM2);

	/* y escribimos un nuevo archivo con la imagen modificada. */
	if ((rwstatus = WriteDibFile(argv[4], &bmFH, &bmIH, &pixM2)) != 0) {
		fprintf(stderr,
		        "\n  %s:: Error No. %d al escribir el archivo %s.\n",
		        argv[0], rwstatus, argv[4]);
		exit(rwstatus);
	}
}


/*_____________________________________________________________________________

  Filtra (pasa a monocromo segun el valor de c = 'B', 'G', 'R') los pixeles
  de un archivo tipo DIB (device-independent bitmap)
  correspondiente a una imagen RGB de 24 bits sin compresion de datos.
_____________________________________________________________________________*/

void FiltrarRGBPixels(char c, int nx, int ny, RGB_PIXEL *pixM, RGB_PIXEL *pixM2)
{
	int ix, iy, kp = 0;

	for (iy  =  0; iy < ny; iy++) {
		for (ix  =  0; ix < nx; ix++) {
			pixM2[kp].blue  = (c == 'B' ? pixM[kp].blue  : 0);
			pixM2[kp].green = (c == 'G' ? pixM[kp].green : 0);
			pixM2[kp].red   = (c == 'R' ? pixM[kp].red   : 0);
			kp++;
		}
	}
}
