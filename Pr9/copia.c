/*
  Este programa copia la entrada estandar (stdin) en la salida estandar (stdout).
  Forma de uso:

	1) Sin reasignar stdin ni stdout ...
 
               $ copia
 
         La copia se detiene al encontrar un EOF (normalmente control-Z).
	   
	2) Reasignando stdin y/o stdout (si el sistema operativo lo permite) ...
	
	         $ copia < nombre_archivo_original > nombre_archivo_copiado

         La copia se detiene al encontrar el final del archivo original (EOF).
         Esta forma de uso permite copiar archivos, pero solo si son de texto.
	   
  Notas:
         getchar() es equivalente a getc(stdin)
	   putchar(c) es equivalente a putc(c, stdout)
*/

#include <stdlib.h>
#include <stdio.h>

int main(void)
{
	int  c;

	while ((c = getchar()) != EOF) {
		putchar(c);
	}

	exit(0);
}
