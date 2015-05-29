/* Estructura q contiene la informacion de un punto BMP en las coordenadas RGB*/
struct ColorRGB {
    int r;
    int g;
    int b;
};

/* Estructura q contiene la informacion de un punto BMP en las coordenadas HSL*/
struct ColorHSL{
    int H;
    double S;
    double L;
};

// Prototype
struct ColorRGB HSLtoRGB (int, double, double);
struct ColorHSL RGBtoHSL (int, int, int);