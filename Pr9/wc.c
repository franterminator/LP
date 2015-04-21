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
    //Prototype
    char isSeparator (char );
    
    int  c;               //char que se lee del stdin
    int letra = 0;        //numero de letra
    int palabra = 0;      //numero de palabra
    int linea = 1;        //numero de linea
    char finPalabra = 0;  //boolean para contar palabra

    while ((c = getchar()) != EOF) {
        //Nueva letra o caracter
        letra++;
        //Nueva palabra
        if(isSeparator(c) == 1){
            finPalabra = 1;
        }
        else if (finPalabra == 1) {
            palabra++;
            finPalabra = 0;
        }
        
        //Fin de línea
        if(c == '\n')
            linea++;
            
    }
    printf("\n%d %d %d\n",letra,palabra,linea);
    fflush(stdin);
    getchar();
    return 0;
}
/* isSeparator comments:
  Fuction to determine if one char is a word separator such as ' ' '\t' '\n'
     Parameter: char c
     Return: 1 if char is separator, otherwise 0
*/
char isSeparator (char c) {
    if (c == ' ') return 1;
    if (c == '\t') return 1;
    if (c == '\n') return 1;
    return 0;
}
