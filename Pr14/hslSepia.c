#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "C-Lib\bmp.h"
#include "C-Lib\HSL.h"

#define max(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })

#define min(a,b) \
    ({ __typeof__ (a) _a = (a) ; \
    __typeof__ (b) _b = (b); \
    _a < _b ? _a : _b; })
    
    
    
    
int main(int argc, char *argv[])
{
    // Prototype
    void sepiaColor(int, int, RGB_PIXEL *);
    
	BITMAPFILEHEADER	bmFH;
	BITMAPINFOHEADER	bmIH;
	RGB_PIXEL         *pixM;

	int nx, ny;
	int rwstatus;

	if (argc != 3) {
		fprintf(stderr,
		        "\n  %s:: Error: introduzca dos nombres de archivo.\n",
		        argv[0]);
		fprintf(stderr,
		        "\n  %s:: Uso  : %s archivo.bmp archivo_I.bmp.\n\n",
		        argv[0], argv[0]);
		exit(1);
	}

	/* Leemos el archivo, */
	if ((rwstatus = ReadDibFile(argv[1], &bmFH, &bmIH, &pixM)) != 0) {
		fprintf(stderr,
		        "\n  %s:: Error No. %d al leer el archivo %s.\n",
		        argv[0], rwstatus, argv[1]);
		exit(rwstatus);
	}

	/* identificamos las dimensiones de la imagen RGB, */
	nx = bmIH.biWidth;
	ny = bmIH.biHeight;

	/* invertimos la imagen */
	fprintf(stderr,
	        "\n\n  Procesando imagen %d x %d ...\n",
	        nx, ny);        
	sepiaColor(nx, ny, pixM);

	/* y escribimos un nuevo archivo con la imagen modificada. */
	if ((rwstatus = WriteDibFile(argv[2], &bmFH, &bmIH, &pixM)) != 0) {
		fprintf(stderr,
		        "\n  %s:: Error No. %d al escribir el archivo %s.\n",
		        argv[0], rwstatus, argv[2]);
		exit(rwstatus);
	}
}

void sepiaColor(int nx, int ny, RGB_PIXEL *pixM)
{
    // Variables
    int ix, iy, kp = 0;
   
    struct ColorRGB rgb;
    struct ColorHSL hsl;
    
    
    for (iy  =  0; iy < ny; iy++) {
        for (ix  =  0; ix < nx; ix++) {
            // Calculate the sepia color
            hsl = RGBtoHSL(pixM[kp].red,pixM[kp].green,pixM[kp].blue);
            rgb = HSLtoRGB (35,hsl.S,hsl.L);
            printf("\n[%d,%f,%f] -> [%d,%d,%d]",hsl.H,hsl.S,hsl.L,rgb.r,rgb.g,rgb.b);
                
            // Modified the hsl color
            pixM[kp].blue = rgb.b < 255 ? rgb.b : 255;
            pixM[kp].green = rgb.g< 255 ? rgb.g : 255;
            pixM[kp].red = rgb.r < 255 ? rgb.r : 255;
                
            kp++;
        }
    }
}


/*
  Converts a HSL color value to RGB. Conversion formula
  adapted from http://en.wikipedia.org/wiki/HSL_color_space.
  Assumes h, s, and l are contained in the set [0,1] and returns
  r, g, and b in the set [0,255].

  @param    int        h      The hue
  @param    double     s      The saturation
  @param    double     l      The lightness
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
 
