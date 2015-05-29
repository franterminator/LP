#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "HSL.h"

#define max(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })

#define min(a,b) \
    ({ __typeof__ (a) _a = (a) ; \
    __typeof__ (b) _b = (b); \
    _a < _b ? _a : _b; })

/*
  Converts a HSL color value to RGB. Conversion formula
  adapted from http://en.wikipedia.org/wiki/HSL_color_space.
  Assumes h, s, and l are contained in the set [0,1] and returns
  r, g, and b in the set [0,255].

  @param    int        h      The hue
  @param    int        s      The saturation
  @param    int        l      The lightness
  @return   structure  rgb    The RGB representation
*/


struct ColorRGB HSLtoRGB (int H,double S, double L) {
    // Prototype
    void modify (double , double , double , double*);
    
    struct ColorRGB rgb;

    double C = (1 - fabs(2*L-1))*S;
    double X = H/60; X = C * (1 - fabs(fmod(X,2) - 1));
    double m = L - C/2;

    double modified[3];
    modify(H,C,X,modified);

    double temp = (modified[0]+m)*255;
    rgb.r = temp < 255 ? temp : 255;

    temp = (modified[1]+m)*255;
    rgb.g = temp < 255 ? temp : 255;

    temp = (modified[2]+m)*255;
    rgb.b = temp < 255 ? temp : 255;

    return rgb;
}

void modify (double H, double C, double X, double* modified) {
    
    if( H >= 0 && H < 60) {
        modified[0]=C;
        modified[1]=X;
        modified[2]=0;
    }
    if ( H>= 60 && H < 120) {
        modified[0]=X;
        modified[1]=C;
        modified[2]=0;
    }
    if ( H >= 120 && H < 180) {
        modified[0]=0;
        modified[1]=C;
        modified[2]=X;
    }
    if ( H >= 180 && H < 240) {
        modified[0]=0;
        modified[1]=X;
        modified[2]=C;
    }   
    if ( H >= 240 && H < 300) {
        modified[0]=X;
        modified[1]=0;
        modified[2]=C;
    }
    if ( H >= 300 && H < 360) {
        modified[0]=C;
        modified[1]=0;
        modified[2]=X;
    }
}

struct ColorHSL RGBtoHSL (int R,int G, int B) {
    // Prototype
    double max3 (int , int , int);
    double min3 (int , int , int);


    struct ColorHSL hsl;
  
    double Cmax = max3(R,G,B);
    double Cmin = min3(R,G,B);
    double dif = Cmax - Cmin;

    int H;
    if( dif == 0 ) H = 0;
    else if ( Cmax == R ) H = 60 * fmod((G-B)/dif,6);
    else if ( Cmax == G ) H = 60 * ((B-R)/dif + 2);
    else if ( Cmax == B ) H = 60 * ((R-G)/dif + 4);

    double L = (Cmax + Cmin)/510;

    double S;
    if ( dif == 0 ) S = 0;
    else S = dif/255/(1-fabs(2*L-1));

    hsl.H = H;
    hsl.S = S;
    hsl.L = L;

    return hsl;
}

double max3 (int R, int G, int B) {
    return max(max(R,G),max(G,B));
}

double min3 (int R, int G, int B) {
    return min(min(R,G),min(G,B));
}
 
