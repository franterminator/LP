#include <math.h>
#include "header.h"

struct Player randomPlayer (int seed) {
    int id = 1;
    double shoot = 0.25*0.25;
    double prize;
    if (shoot == 0.75) prize = 300.20;
    else prize = 200.15;

    struct Player fran;
    fran.id = id;
    fran.shoot = shoot;
    fran.prize = prize;

    return fran;
}
