/*
  Este programa muestra los bits de un archivo (1 bit <-> 1 digito en base 2).
  Forma de uso:
               > vuelca nombre_archivo_original nombre_archivo_volcado
*/

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#define NCL  8   /* numero de caracteres por linea */

int main(int argc, char *argv[])
{
	FILE *fpIn,
	     *fpOut;

	int  c,
	     ncl = 0, nct = 0;

	char text[NCL + 1];

	int  nclMax = NCL;

	if (argc != 3) {
		printf("%s: introduzca dos nombres de archivo\n", argv[0]);
		exit(1);
	} 

	if ((fpIn = fopen(argv[1], "rb")) == NULL) {
		printf("%s: imposible abrir el archivo %s para lectura\n", argv[0], argv[1]);
		exit(2);
	}

	if ((fpOut = fopen(argv[2], "wb")) == NULL) {
		printf("%s: imposible abrir el archivo %s para escritura\n", argv[0], argv[2]);
		exit(3);
	}

	text[NCL] = '\0';

	/* Leemos el archivo de entrada */
	while ((c = getc(fpIn)) != EOF) {
	
		/* Al principio de la linea se indican los bytes que se mostraran */
		if (ncl == 0)
			fprintf(fpOut, "[%10.10d-%10.10d] :: ", nct + 1, nct + nclMax);
		
		/* Si el caracter no es imprimible se pone un punto centrado */
		text[ncl++] = isprint(c) ? c : '·';
		
		/* Escribimos el byte en forma de 8 bits, */
		{
			int  b;
			for (b = 7; b >= 0; b--)
				fprintf(fpOut, "%1d", (unsigned) (c >> b & ~(~0 << 1)));
			
		}

		/* En su caso, ... */
		if (++nct % nclMax == 0) {          /* ... terminamos la fila ... */
			fprintf(fpOut, " <-> %s\n", text);
			ncl = 0;
		
		} else {
			fprintf(fpOut, " ");          /* ... o ponemos un separador */
		}
	
		/* Dejamos una linea en blanco cada KiB */
		if (nct % 1024 == 0)
			fprintf(fpOut, "\n");
	}

	/* Rellenamos con blancos la ultima linea y la terminamos */
	if (ncl > 0) {
		while (ncl < nclMax) {
			text[ncl++] = ' ';
			fprintf(fpOut, "         ");
		}
	
		fprintf(fpOut, " <-> %s\n", text);
	}

	/* Finalmente indicamos cuantos bytes se han procesado */
	printf("%s: %10d bytes volcados\n", argv[0], nct);

	exit(0);

}
