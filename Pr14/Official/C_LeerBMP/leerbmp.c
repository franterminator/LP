/*_____________________________________________________________________________

  Lee y muestra el contenido
  de un archivo tipo DIB (device-independent bitmap)
  correspondiente a una imagen RGB de 24 bits sin compresion de datos.

  Uso: leerbmp archivo.bmp
_____________________________________________________________________________*/


#include <stdlib.h>
#include <stdio.h>
#include "../C-Lib/bmp.h"

int main(int argc, char *argv[])
{
	void ShowDibHeaders(BITMAPFILEHEADER *, BITMAPINFOHEADER *);
	void ShowRGBPixels(int, int, RGB_PIXEL *);

	BITMAPFILEHEADER	bmFH;
	BITMAPINFOHEADER	bmIH;
	RGB_PIXEL         *pixM;

	int nx, ny;
	int rwstatus;

	if (argc != 2) {
		fprintf(stderr,
		        "\n  %s: introduzca un nombre de archivo.\n",
		        argv[0]);
		fprintf(stderr,
		        "\n  Uso: %s archivo.bmp.\n\n",
		        argv[0]);
		exit(1);
	}

	/* Leemos el archivo, */
	if ((rwstatus = ReadDibFile(argv[1], &bmFH, &bmIH, &pixM)) != 0) {
		fprintf(stderr,
		        "\n  %s: Error No. %d al leer el archivo %s.\n",
		        argv[0], rwstatus, argv[1]);
		if (rwstatus == 4) ShowDibHeaders(&bmFH, &bmIH);
		exit(rwstatus);
	}

	/* identificamos las dimensiones de la imagen RGB, */
	nx = bmIH.biWidth;
	ny = bmIH.biHeight;

	/* y mostramos el contenido del File Header y del Info Header y los pixeles de la imagen RGB. */
	ShowDibHeaders(&bmFH, &bmIH);
	ShowRGBPixels(nx, ny, pixM);
}


/*_____________________________________________________________________________

  Muestra el contenido del File Header y del Info Header
  de un archivo tipo DIB (device-independent bitmap)
  correspondiente a una imagen RGB de 24 bits sin compresion de datos.

  Se usa la notacion abreviada:
                                ep->m  <-> (*ep).m
______________________________________________________________________________*/

void ShowDibHeaders(BITMAPFILEHEADER *bmFHp, BITMAPINFOHEADER *bmIHp)
{
	/* File Header */
	printf("\n\n  bmFH:\n");
	printf("     .bfType          -> %c%c\n", bmFHp->bfType[0], bmFHp->bfType[1]);
	printf("     .bfSize          -> %d\n",   bmFHp->bfSize);
	printf("     .bfReserved1     -> %d\n",   bmFHp->bfReserved1);
	printf("     .bfReserved2     -> %d\n",   bmFHp->bfReserved2);
	printf("     .bfOffBits       -> %d\n",   bmFHp->bfOffBits);

	/* Info Header */
	printf("\n\n  bmIH:\n");
	printf("     .biSize          -> %d\n",   bmIHp->biSize);
	printf("     .biWidth         -> %d\n",   bmIHp->biWidth);
	printf("     .biHeight        -> %d\n",   bmIHp->biHeight);
	printf("     .biPlanes        -> %d\n",   bmIHp->biPlanes);
	printf("     .biBitCount      -> %d\n",   bmIHp->biBitCount);
	printf("     .biCompression   -> %d\n",   bmIHp->biCompression);
	printf("     .biSizeImage     -> %d\n",   bmIHp->biSizeImage);
	printf("     .biXPelsPerMeter -> %d\n",   bmIHp->biXPelsPerMeter);
	printf("     .biYPelsPerMeter -> %d\n",   bmIHp->biYPelsPerMeter);
	printf("     .biClrUsed       -> %d\n",   bmIHp->biClrUsed);
	printf("     .biClrImportant  -> %d\n",   bmIHp->biClrImportant);
}



/*_____________________________________________________________________________

  Muestra los pixeles
  de un archivo tipo DIB (device-independent bitmap)
  correspondiente a una imagen RGB de 24 bits sin compresion de datos.

  Se usa la notacion abreviada:
                                ep->m  <-> (*ep).m
______________________________________________________________________________*/

void ShowRGBPixels(int nx, int ny, RGB_PIXEL *pixM)
{
	int ix, iy;

	/* Pixeles */
	printf("\n\n  pixM[]:\n");
	for (iy  =  0; iy < ny; iy++) {
		for (ix  =  0; ix < nx; ix++) {
			printf("     ix = %6d, iy = %6d     ->     B = %3d, G = %3d, R = %3d\n",
				 ix, iy, pixM->blue, pixM->green, pixM->red);
			pixM++;
		}
	}
}
