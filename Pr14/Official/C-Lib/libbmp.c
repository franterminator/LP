/*______________________________________________________________________________
________________________________________________________________________________

Funciones para la manipulacion de archivos tipo DIB (device-independent bitmap)
con imagenes RGB de 24 bits sin compresion de datos.

Se basa en el contenido del documento

      "DIBs and Their Use",
      Ron Gery (Microsoft Developer Network Technology Group), March 20, 1992

una parte del cual se transcribe al final del archivo bmp.h

F. Navarrina, 20081223
________________________________________________________________________________
______________________________________________________________________________*/

#include <stdlib.h>
#include <stdio.h>
#include "bmp.h"



/*_____________________________________________________________________________

  Inicializacion del contenido por defecto del File Header y del Info Header
  de un archivo tipo DIB (device-independent bitmap)
  correspondiente a una imagen RGB de 24 bits sin compresion de datos,
  de ancho = nx pixeles, y alto = ny pixeles.

  Se usa la notacion abreviada:
                                ep->m  <-> (*ep).m
______________________________________________________________________________*/

void SetDibHeaders(int nx, int ny,
                   BITMAPFILEHEADER *bmFHp, BITMAPINFOHEADER *bmIHp)
{
	int nbi, nbf;

      /* Bytes de la imagen (en principio = 3 * nx * ny).
         El numero de bytes de cada fila (3 * nx) debe ser multiplo de 4.
         Si no lo es hay que rellenar la fila con bytes adicionales. */
	nbi = ((3 * nx) % 4) == 0 ? 3 * nx * ny : (((3 * nx) / 4 + 1) * 4) * ny;
	
	/* Bytes del archivo = bytes antes de la imagen + bytes de la imagen */
	nbf = BFOFFBITS + nbi;

	/* File Header */
	bmFHp->bfType[0]       =           'B';   /* Tipo de bitmap:           */
	bmFHp->bfType[1]       =           'M';   /*      BM <-> DIB file      */
	bmFHp->bfSize          =           nbf;   /* Bytes del archivo         */
	bmFHp->bfReserved1     =             0;   /* No se usa este campo      */
	bmFHp->bfReserved2     =             0;   /* No se usa este campo      */
	bmFHp->bfOffBits       =     BFOFFBITS;   /* Bytes antes de imagen RGB */

	/* Info Header */

	bmIHp->biSize          =        BISIZE;   /* Bytes del Info Header     */
	bmIHp->biWidth         =            nx;   /* Pixeles segun eje X       */
	bmIHp->biHeight        =            ny;   /* Pixeles segun eje Y       */
	bmIHp->biPlanes        =             1;   /* 1 plano (obligatoriamente)*/
	bmIHp->biBitCount      =    BIBITCOUNT;   /* 24 bits por pixel         */
	bmIHp->biCompression   = BICOMPRESSION;   /* Sin compresion            */
	bmIHp->biSizeImage     =           nbi;   /* Bytes de la imagen RGB    */
	bmIHp->biXPelsPerMeter =             0;   /* Resolucion segun eje X    */
	bmIHp->biYPelsPerMeter =             0;   /* Resolucion segun eje Y    */
	bmIHp->biClrUsed       =             0;   /* No color tables           */
	bmIHp->biClrImportant  =             0;   /* No color tables           */
}



/*_____________________________________________________________________________

  Comprobacion del contenido del File Header y del Info Header
  de un archivo tipo DIB (device-independent bitmap)
  correspondiente a una imagen RGB de 24 bits sin compresion de datos.

  Se usa la notacion abreviada:
                                ep->m  <-> (*ep).m
______________________________________________________________________________*/

int CheckDibHeaders(BITMAPFILEHEADER *bmFHp, BITMAPINFOHEADER *bmIHp)
{
	int nerr = 0;

	/* File Header */
	if (bmFHp->bfType[0] != 'B' || bmFHp->bfType[1] != 'M') {
		nerr++;
		fprintf(stderr,
		        "\n  ... el bitmap no es del tipo BM.\n");
	}
	if (bmFHp->bfOffBits < BFOFFBITS) {
		nerr++;
		fprintf(stderr,
		        "\n  ... indicacion incorrecta del comienzo de la imagen.\n");
	}
	if (bmIHp->biWidth <= 0 || bmIHp->biHeight <= 0) {
		nerr++;
		fprintf(stderr,
		        "\n  ... el ancho o el alto de la imagen no son correctos.\n");
      }
	if (bmIHp->biPlanes != 1) {
		nerr++;
		fprintf(stderr,
		        "\n  ... el numero de planos es incorrecto.\n");
	}
	if (bmIHp->biBitCount != BIBITCOUNT) {
		nerr++;
		fprintf(stderr,
		        "\n  ... no se trata de una imagen RGB de %d bits.\n",
		       BIBITCOUNT);
	}
	if (bmIHp->biCompression != BICOMPRESSION) {
		nerr++;
		fprintf(stderr,
			  "\n  ... tipo de compresion de datos no soportado.\n");
	}
	if (bmIHp->biClrUsed != 0 || bmIHp->biClrImportant != 0) {
		nerr++;
		fprintf(stderr,
		        "\n  ... color tables no soportadas.\n");
	}

	return nerr;
}



/*_____________________________________________________________________________

  Lectura de un archivo tipo DIB
_____________________________________________________________________________*/

int ReadDibFile(char *filename,
                BITMAPFILEHEADER *bmFHp, BITMAPINFOHEADER *bmIHp,
                RGB_PIXEL **pixMp)
{
	FILE      *infile;
	int	    nx, ny;

	/* Abrimos el archivo, */
	if ((infile  =  fopen(filename, "rb")) == NULL) {
		fprintf(stderr,
			  "\n  Error: no se puede abrir el archivo [%s].\n",
		       filename);
		return 1;
	}

	/* leemos el File Header, */
	if (fread(bmFHp, sizeof(BITMAPFILEHEADER), 1, infile) != 1) {
		fprintf(stderr,
			  "\n  Error: no se puede leer el file header [%s].\n",
		       filename);
		return 2;
	}

	/* leemos el Info Header, */
	if (fread(bmIHp, sizeof(BITMAPINFOHEADER), 1, infile) != 1) {
		fprintf(stderr,
			  "\n  Error: no se puede leer el info header [%s].\n",
		       filename);
		return 3;
	}

	/* comprobamos la consistencia del File Header y del Info Header, */
	if (CheckDibHeaders(bmFHp, bmIHp) != 0) {
		fprintf(stderr,
			  "\n  Error: inconsistencias en los headers [%s].\n",
		        filename);
		return 4;
	}

	/* nos situamos al comienzo de la imagen RGB, */
	if (fseek(infile, bmFHp->bfOffBits, SEEK_SET) != 0) {
		fprintf(stderr,
			  "\n  Error: no se puede preparar la lectura de la imagen [%s].\n",
		       filename);
		return 5;
	}

	/* identificamos las dimensiones de la imagen RGB, */
	nx = bmIHp->biWidth;
	ny = bmIHp->biHeight;

	/* solicitamos memoria para almacenar la imagen,*/
	if ((*pixMp = (RGB_PIXEL *) malloc(sizeof(RGB_PIXEL) * nx * ny)) == NULL) {
		fprintf(stderr,
			  "\n  Error: no hay memoria suficiente para la imagen %d x %d [%s].\n",
		       nx, ny, filename);
		return 6;
	}

	/* leemos la imagen RGB, */
	if (ReadImageRGB(infile, nx, ny, *pixMp) != 0) {
		fprintf(stderr,
			  "\n  Error: no se puede leer la imagen RGB [%s].\n",
		        filename);
		return 7;
	}

	/* y cerramos el archivo */
	if (fclose(infile) != 0) {
		fprintf(stderr,
			  "\n  Error: no se puede cerrar el archivo [%s].\n",
		       filename);
		return 8;
	}

	return 0;
}



/*_____________________________________________________________________________

  Escritura de un archivo tipo DIB
_____________________________________________________________________________*/


int WriteDibFile(char *filename,
                 BITMAPFILEHEADER *bmFHp, BITMAPINFOHEADER *bmIHp,
                 RGB_PIXEL **pixMp)
{
	FILE      *outfile;
	int	    nx, ny;

	/* Abrimos el archivo, */
	if ((outfile  =  fopen(filename, "wb")) == NULL) {
		fprintf(stderr,
			  "\n  Error: no se puede abrir el archivo [%s].\n",
		        filename);
		return 1;
	}

	/* colocaremos la imagen a continuacion del Info Header, */
	bmFHp->bfOffBits = BFOFFBITS;

	/* escribimos el File Header, */
	if (fwrite(bmFHp, sizeof(BITMAPFILEHEADER), 1, outfile) != 1) {
		fprintf(stderr,
			  "\n  Error: no se puede escribir el file header [%s].\n",
			  filename);
		return 2;
	}

	/* escribimos el Info Header, */
	if (fwrite(bmIHp, sizeof(BITMAPINFOHEADER), 1, outfile) != 1) {
		fprintf(stderr,
			  "\n  Error: no se puede escribir el info header [%s].\n",
		        filename);
		return 3;
	}

	/* identificamos las dimensiones de la imagen RGB, */
	nx = bmIHp->biWidth;
	ny = bmIHp->biHeight;

	/* volcamos la imagen RGB */
	if (WriteImageRGB(outfile, nx, ny, *pixMp) != 0) {
		fprintf(stderr,
			  "\n  Error: no se puede escribir la imagen RGB [%s].\n",
		        filename);
		return 7;
	}


	/* y cerramos el archivo */
	if (fclose(outfile) != 0) {
		fprintf(stderr,
			  "\n  Error: no se puede cerrar el archivo [%s].\n",
		        filename);
		return 8;
	}

	return 0;
}



/*_____________________________________________________________________________

  Lectura de una imagen RGB
_____________________________________________________________________________*/

int ReadImageRGB(FILE *infile, int nx, int ny, RGB_PIXEL *pixM)
{
	int           np, iy, nc;
	unsigned char bufc[3];

	/* bytes adicionales por fila para que el total sea multiplo de 4 */
	nc = 4 - ((nx * 3) % 4); if (nc == 4) nc = 0;

	if (nc == 0) {    /* leemos la imagen de un tiron */
		np = nx * ny;
		if (fread(pixM, sizeof(RGB_PIXEL), np, infile) != np) {
			return 1;
		}

	} else {            /* leemos cada linea con los bytes adicionales */
		for (iy = 0; iy < ny; iy++, pixM += nx) { 
			if (fread(pixM, sizeof(RGB_PIXEL),     nx, infile) != nx)
				return 2;
			if (fread(bufc, sizeof(unsigned char), nc, infile) != nc)
				return 3;
		}
	}
	return 0;
}



/*_____________________________________________________________________________

  Escritura de una imagen RGB
_____________________________________________________________________________*/

int WriteImageRGB(FILE *outfile, int nx, int ny, RGB_PIXEL *pixM)
{
	int           np, iy, nc;
	unsigned char bufc[3];

	/* bytes adicionales por fila para que el total sea multiplo de 4 */
	nc = 4 - ((nx * 3) % 4); if (nc == 4) nc = 0;

	if (nc == 0) {    /* escribimos la imagen de un tiron */
		np = nx * ny;
		if (fwrite(pixM, sizeof(RGB_PIXEL), np, outfile) != np) {
			return 1;
		}

	} else {            /* escribimos cada linea con los bytes adicionales */
		for (iy = 0; iy < ny; iy++, pixM += nx) { 
			if (fwrite(pixM, sizeof(RGB_PIXEL),     nx, outfile) != nx)
				return 2;
			if (fwrite(bufc, sizeof(unsigned char), nc, outfile) != nc)
				return 3;
		}
	}
	return 0;
}
