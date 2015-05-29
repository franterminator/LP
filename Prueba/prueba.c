#include <stdlib.h>
#include <stdio.h>
#include "C-Lib/header.h"

int main(void)
{
    struct Player randomPlayer(int seed);
    struct Player fran;

    fran = randomPlayer(3);
    printf("\nId: %d;\nNombre: Fran;\nPorcentaje: %f;\nPrecio: %f",fran.id,fran.shoot,fran.prize);
    
    fflush(stdin);
    getchar();
    return 0;
} 
