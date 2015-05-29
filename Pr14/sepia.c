/*_____________________________________________________________________________

  Cambia a una escala de grises un
  un archivo tipo DIB (device-independent bitmap)
  correspondiente a una imagen RGB de 24 bits sin compresion de datos.

  Uso: invertirbmp archivo.bmp archivo_I.bmp
_____________________________________________________________________________*/


#include <stdlib.h>
#include <stdio.h>
#include "C-Lib\bmp.h"


int main(int argc, char *argv[])
{
    void sepiaColor(int, int, RGB_PIXEL *);

	BITMAPFILEHEADER	bmFH;
	BITMAPINFOHEADER	bmIH;
	RGB_PIXEL         *pixM;

	int nx, ny;
	int rwstatus;

	if (argc != 3) {
		fprintf(stderr,
		        "\n  %s:: Error: introduzca dos nombres de archivo.\n",
		        argv[0]);
		fprintf(stderr,
		        "\n  %s:: Uso  : %s archivo.bmp archivo_I.bmp.\n\n",
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

	/* invertimos la imagen */
	fprintf(stderr,
	        "\n\n  Procesando imagen %d x %d ...\n",
	        nx, ny);        
	sepiaColor(nx, ny, pixM);

	/* y escribimos un nuevo archivo con la imagen modificada. */
	if ((rwstatus = WriteDibFile(argv[2], &bmFH, &bmIH, &pixM)) != 0) {
		fprintf(stderr,
		        "\n  %s:: Error No. %d al escribir el archivo %s.\n",
		        argv[0], rwstatus, argv[2]);
		exit(rwstatus);
	}
}

/*_____________________________________________________________________________

  Pasa los colores a sepia
  un archivo tipo DIB (device-independent bitmap)
  correspondiente a una imagen RGB de 24 bits sin compresion de datos.
_____________________________________________________________________________*/

void sepiaColor(int nx, int ny, RGB_PIXEL *pixM)
{
	int ix, iy, kp = 0;

	for (iy  =  0; iy < ny; iy++) {
		for (ix  =  0; ix < nx; ix++) {
                    // Calculate the sepia color
                    double blue = (double)pixM[kp].red*0.272+(double)pixM[kp].green*0.534 + (double)pixM[kp].blue*0.131;
                    double green = (double)pixM[kp].red*0.349 + (double)pixM[kp].green*0.686 + (double)pixM[kp].blue*0.168;
                    double red = (double)pixM[kp].red*0.393 + (double)pixM[kp].green*0.769 + (double)pixM[kp].blue*0.189;
                    
                    // Modified the original color
                    pixM[kp].blue = blue < 255 ? blue : 255;
                    pixM[kp].green = green < 255 ? green : 255;
                    pixM[kp].red = red < 255 ? red : 255;
                    
                    kp++;
		}
	}
}
