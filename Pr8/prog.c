/*
  Este programa lee un string (cadena) de caracteres e invierte su orden.

  Notas:

    El string se almacena en un vector de variables tipo char.
    Se utiliza el convenio tipico de C (la cadena termina con un NULL).
    Se utilizan punteros como alternativa a los componentes de vectores.
    Se introducen algunos conceptos avanzados.

  Posibles problemas resueltos:

    El string puede contener espacios porque no se lee con la funcion scanf().
    Se controla el maximo numero de caracteres que se leen.
      [ => se evitan posibles invasiones de memoria ]
*/

#include <stdlib.h>
#include <stdio.h>

// Simbolo que cambia dos valores char
#define SWAPCHAR(a,b) {char c; c = a; a = b; b = c;}

int main(void)
{
    #define MX 132	/* creamos espacio para un maximo de 132 caracteres */

    void leeString(char *, int);
    void modificaString(char *);
    void invierteString(char *);

    char s[MX + 1];

    printf("\n Introduzca string : ");
    leeString(s, MX);    //Lee los caracteres que se introducen por teclado 

    modificaString(s);   //Cambia mayusculas por minusculas y viceversa
    printf("\n String modificado -> %s\n", s);
    
    invierteString(s);   //Cambia de orden los caracteres

    printf("\n String modificado y invertido -> %s\n", s);

    fflush(stdin); getchar();
    exit(0);
}


/*______________________________________________________________________________
  LeeString: lee un string
    -> Parameter: int n, el tamaño del string
    -> Modify: char s, lee del teclado el string de tamaño n
    -> Return: void
*/

void leeString(char *s, int n)
{
    for( ; (*s = getchar()) != '\n' && n > 0; s++, n--) ;

    *s = '\0';	/* fin de string */
}
/*______________________________________________________________________________
  tamañoString: cambia las mayusculas por minuculas y viceversa
    -> Parameter: void
    -> Modify: char s, cambia el tamaño de los caracteres de s
    -> Return: void
 */

void modificaString (char *s) {
    char *p;
    for (p = s; *p != '\0'; p++) ; 	/* hallamos el final del string */
    for ( ; s<p; s++) {
        //Mayusculas?
        if((*s >= 'A') && (*s <= 'Z'))
            *s-= ('A' - 'a');
        //minusculas?
        else if ((*s >= 'a') && (*s <= 'z'))
            *s += ('A' - 'a');
    }
}

/*______________________________________________________________________________
  InvierteString: invierte el orden de un string
    -> Parameter: void
    -> Modify: char s, modifica de orden los caracteres del char
    -> Return: void
*/

void invierteString(char *s)
{
    char *p;

    for (p = s; *p != '\0'; p++) ; 	/* hallamos el final del string */

    for (p--; s < p; s++, p--)
        SWAPCHAR(*s, *p) //;
}
