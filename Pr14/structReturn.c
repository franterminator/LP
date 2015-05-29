/*_____________________________________________________________________________

  Cambia a una escala de grises un
  un archivo tipo DIB (device-independent bitmap)
  correspondiente a una imagen RGB de 24 bits sin compresion de datos.

  Uso: invertirbmp archivo.bmp archivo_I.bmp
_____________________________________________________________________________*/


#include <stdlib.h>
#include <stdio.h>
#include "C-Lib\bmp.h"
#include "C-Lib\HSL.h"

int main(int argc, char *argv[])
{
    // Prototype
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

void sepiaColor(int nx, int ny, RGB_PIXEL *pixM)
{
    // Variables
    int ix, iy, kp = 0;
   
    struct ColorRGB rgb;
    struct ColorHSL hsl;
    
    
    for (iy  =  0; iy < ny; iy++) {
        for (ix  =  0; ix < nx; ix++) {
            // Calculate the sepia color
            hsl = RGBtoHSL(pixM[kp].red,pixM[kp].green,pixM[kp].blue);
            rgb = HSLtoRGB (34,hsl.S,hsl.L+0.15);
            printf("\n[%d,%f,%f] -> [%d,%d,%d]",hsl.H,hsl.S,hsl.L,rgb.r,rgb.g,rgb.b);
                
            // Modified the hsl color
            pixM[kp].blue = rgb.b < 255 ? rgb.b : 255;
            pixM[kp].green = rgb.g< 255 ? rgb.g : 255;
            pixM[kp].red = rgb.r < 255 ? rgb.r : 255;
                
            kp++;
        }
    }
}

