#define HELP \
"											\n\
  Este programa muestra								\n\
											\n\
	  a) los bytes (1 byte <-> 2 digitos en base 16) o		\n\
	  b) los bits  (1 bit  <-> 1 digito  en base 2)			\n\
											\n\
  que componen un archivo.							\n\
											\n\
  Forma de uso:									\n\
											\n\
	> vuelca [InputFileName] [-o OutputFileName] [-B | -b] [-s] \n\
											\n\
    tambien:									\n\
											\n\
	> vuelca  InputFileName  [   OutputfileName] [-B | -b] [-s] \n\
											\n\
  OPCIONES										\n\
											\n\
	-B										\n\
		Muestra bytes (1 byte <-> 2 digitos en base 16).	\n\
		Esta es la opcion por defecto.				\n\
											\n\
	-b										\n\
		Muestra bits  (1 bit  <-> 1 digito  en base 2).		\n\
		La opcion por defecto es -B.					\n\
											\n\
	-S, -s									\n\
		Sin informacion adicional					\n\
		(numeracion de bytes y significado alfanumerico).	\n\
											\n\
	-O, -o  OutputFileName							\n\
											\n\
		Nombre del archivo de salida.					\n\
		Si se omite, se utilizara el archivo out.txt.		\n\
											\n\
	--help									\n\
											\n\
		Imprime esta informacion.					\n\
											\n\
  OPERANDOS										\n\
											\n\
	InputFileName								\n\
											\n\
		Nombre del archivo de entrada.				\n\
		Si se omite, se utilizara la entrada estandar (stdin).\n\
											\n\
	OutputFileName								\n\
											\n\
		Nombre del archivo de salida.					\n\
		Si se omite, se utilizara el archivo out.txt.		\n\
											\n\
"

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define NCLB 32  /* numero de caracteres por linea cuando se muestran bytes */
#define NCLb  8  /* numero de caracteres por linea cuando se muestran bits  */
#define NCL  32  /* maximo de los dos anteriores                            */

#ifndef FALSE
	#define FALSE 0
#endif

#ifndef TRUE
	#define TRUE !FALSE
#endif

#define INDEFINIDO -1

int main(int argc, char *argv[])
{
	void Volcar(char *, FILE *, FILE *, int, int, int);
	void FatalError(char *, char *, char *, int);

	FILE *fpIn  = stdin,
           *fpOut = NULL;

	int  VerBits = INDEFINIDO, AdInfo = INDEFINIDO,
	     nclMax;

	char *InputFileName  = NULL,
	     *OutputFileName = NULL;


	/* Procesamiento del command-line: argv se interpreta como un vector de punteros */

	int iarg;

	for (iarg=1; iarg < argc; iarg++) {
		char *c;
		c = argv[iarg];

	      if (*c == '-') {  /* Opciones ... */
			c++;
			if (*c == '-') {	/* ... de varias letras */
				c++;
				if (strcmp(c, "help") == 0) {
					fprintf(stderr, "\n%s:\n%s\n", argv[0], HELP);
					exit(0);

				} else FatalError("%s: opcion desconocida [%s]\n", argv[0], argv[iarg], 1);

			} else if ((strlen(c) == 1) && (strchr("Oo", *c))) { /* ... de 1 letra con arg. adicional */
				if (iarg + 1 == argc)
					FatalError("%s: falta argumento de [%s]\n", argv[0], argv[iarg], 5);
				else
					switch (*c) {
						case 'O': case 'o':
							iarg++;
							if (OutputFileName == NULL) OutputFileName = argv[iarg];
							else FatalError("%s: varios OutputFiles\n", argv[0], NULL, 6);
							break;

					}

			} else {		/* ... de otra letra sin argumentos adicionales (por separado o agrupada) */
				while(*c != '\0')
					switch (*c) {
						case 'B':
							if (VerBits == INDEFINIDO) VerBits = FALSE;
							else FatalError("%s: varias opciones [-B | -b]\n", argv[0], NULL, 4);
							c++; break;	/* siguiente letra */

						case 'b':
							if (VerBits == INDEFINIDO) VerBits = TRUE;
							else FatalError("%s: varias opciones [-B | -b]\n", argv[0], NULL, 4);
							c++; break;	/* siguiente letra */

						case 'S': case 's':
							if (AdInfo == INDEFINIDO) AdInfo = FALSE;
							else FatalError("%s: varias opciones [-S | -s]\n", argv[0], NULL, 4);
							c++; break; /* siguiente letra */

						default:
							FatalError("%s: opcion desconocida [%s]\n", argv[0], argv[iarg], 1);
							c++; break; /* siguiente letra, si se da el caso */

					}
	
			}

		} else {	      /* Operandos: InputFile o OutputFile */
			if (InputFileName == NULL) InputFileName = argv[iarg];
			else if (OutputFileName == NULL) OutputFileName = argv[iarg];
			else FatalError("%s: varios OutputFiles\n", argv[0], NULL, 6);

		}

	}


	/* Opciones por defecto */

	if (VerBits == INDEFINIDO) VerBits = FALSE;
	if (AdInfo == INDEFINIDO) AdInfo = TRUE;

	/* Apertura de archivos (en su caso) */

	if (InputFileName) {
		if (!(fpIn  = fopen(InputFileName, "rb")))
			FatalError("%s: imposible abrir el archivo %s para lectura\n",
				argv[0], InputFileName, 2);
	}

	if (OutputFileName) {
		if (!(fpOut = fopen(OutputFileName, "wb")))
			FatalError("%s: imposible abrir el archivo %s para escritura\n",
			       argv[0], OutputFileName, 3);
	} else {
		if (!(fpOut = fopen("out.txt", "wb")))
			FatalError("%s: imposible abrir el archivo %s para escritura\n",
			       argv[0], "out.txt",3);
	}


	/* Volcado */

	Volcar(argv[0], fpIn, fpOut, VerBits, AdInfo, VerBits ? NCLb : NCLB);


	exit(0);

}


/*____________________________________________________________________Volcar__*/

void Volcar(char *ProgName, FILE *fpIn, FILE *fpOut, int VerBits, int AdInfo, int nclMax)
{
	int  c,
	     ncl = 0, nct = 0;

	char text[NCL + 1];

	text[nclMax] = '\0';

	/* Leemos el archivo de entrada */
	while ((c = getc(fpIn)) != EOF) {
	
		/* Al principio de la linea se indican los bytes que se mostraran */
		if (AdInfo && (ncl == 0))
			fprintf(fpOut, "[%10.10d-%10.10d] :: ", nct + 1, nct + nclMax);
		
		/* Si el caracter no es imprimible se pone un punto centrado */
		if (AdInfo) text[ncl++] = isprint(c) ? c : '·';
		
		/* Escribimos el byte en forma de ... */
		if (VerBits) {                                     /* ... 8 bits, */
			int  b;
			for (b = 7; b >= 0; b--)
				fprintf(fpOut, "%1d", (unsigned) (c >> b & ~(~0 << 1)));
			
		} else {                            /* ... o de dos hexadecimales */ 
				fprintf(fpOut, "%2.2X", c);
		}

		/* En su caso, ... */
		if (++nct % nclMax == 0) {              /* ... terminamos la fila */
			if (AdInfo) fprintf(fpOut, " <-> %s\n", text);
			else fprintf(fpOut,"\n");
			ncl = 0;
		
		} else {
			if (VerBits) fprintf(fpOut, " "); /* o ponemos un separador */
		}
	
		/* Dejamos una linea en blanco cada KiB */
		if (nct % 1024 == 0)
			fprintf(fpOut, "\n");
	}

	/* Rellenamos con blancos la ultima linea y la terminamos */
	if (ncl > 0) {
		while (ncl < nclMax) {
			if (AdInfo) text[ncl++] = ' ';
			if (VerBits) {
				fprintf(fpOut, "         ");
			} else {
				fprintf(fpOut, "  ");
			}
		}
	
		if (AdInfo) fprintf(fpOut, " <-> %s\n", text);
		else fprintf(fpOut,"\n");
	}

	/* Finalmente indicamos cuantos bytes se han procesado */
	fprintf(stderr, "%s: %10d bytes volcados\n", ProgName, nct);

}

/*________________________________________________________________FatalError__*/

void FatalError(char *formato, char *ProgName, char *argumento, int ierr)
{
	fprintf(stderr, formato, ProgName, argumento);
	exit(ierr);
}
