/*______________________________________________________________________________
________________________________________________________________________________

Definición de estructuras de datos para el procesamiento de archivos tipo DIB
(device-independent bitmap) con imagenes RGB de 24-bits sin compresion.

Se basa en el contenido del documento

      "DIBs and Their Use",
      Ron Gery (Microsoft Developer Network Technology Group), March 20, 1992

una parte del cual se transcribe al final.

F. Navarrina, 20081223
________________________________________________________________________________
______________________________________________________________________________*/



/*_____________________________________________ Por defecto ...               */
#define BFHSIZE                                    14  /* bytes File Header   */
#define BISIZE                                     40  /* bytes Info Header   */
#define BFOFFBITS                    BFHSIZE + BISIZE  /* comienzo de imagen  */           
#define BIBITCOUNT                                 24  /* bits por color      */
#define BICOMPRESSION                               0  /* RGB sin compresion  */



/*_____________________________________________ Garantizamos que los headers
                                                tendran el numero de bytes
                                                indicado, aunque no sea
                                                multiplo de long. de palabra  */
#pragma pack(push, 1)



/*_____________________________________________ Bitmap File Header            */
typedef struct { 
	unsigned char  bfType[2];                        /* Tipo de BMP         */
	unsigned int   bfSize;                           /* Bytes del archivo   */
	unsigned short bfReserved1;                      /* Reservado 1         */
	unsigned short bfReserved2;                      /* Reservado 2         */
	unsigned int   bfOffBits;                        /* Comienzo de imagen  */
} BITMAPFILEHEADER;



/*_____________________________________________ Bitmap Info Header            */
typedef struct { 
	unsigned int   biSize;                           /* Bytes Info Header   */
	unsigned int   biWidth;                          /* Pixeles segun eje X */
	unsigned int   biHeight;                         /* Pixeles segun eje Y */
	unsigned short biPlanes;                         /* Capas               */
	unsigned short biBitCount;                       /* Bits por color      */
	unsigned int   biCompression;                    /* Compresion          */
	unsigned int   biSizeImage;                      /* Bytes de la imagen  */
	unsigned int   biXPelsPerMeter;                  /* Res. x en pixeles/m */
	unsigned int   biYPelsPerMeter;                  /* Res. y en pixeles/m */
	unsigned int   biClrUsed;                        /* Tabla de colores    */ 
	unsigned int   biClrImportant;                   /* Colores esenciales  */
} BITMAPINFOHEADER;



/*_____________________________________________ Pixel RGB de 24 bits          */
typedef struct { 
	unsigned char blue;                              /* Coord. B : 0 - 255  */
	unsigned char green;                             /* Coord. G : 0 - 255  */
	unsigned char red;                               /* Coord. R.: 0 - 255  */
} RGB_PIXEL; 



/*_____________________________________________ Prototipos de Funciones       */

void SetDibHeaders  (int, int, BITMAPFILEHEADER *, BITMAPINFOHEADER *);
int  CheckDibHeaders(          BITMAPFILEHEADER *, BITMAPINFOHEADER *);

int  ReadDibFile (char *, BITMAPFILEHEADER *, BITMAPINFOHEADER *, RGB_PIXEL **);
int  WriteDibFile(char *, BITMAPFILEHEADER *, BITMAPINFOHEADER *, RGB_PIXEL **);

int  ReadImageRGB (FILE *, int, int, RGB_PIXEL *);
int  WriteImageRGB(FILE *, int, int, RGB_PIXEL *);

/*______________________________________________________________________________
________________________________________________________________________________

Transcripción parcial del documento:
      "DIBs and Their Use",
      Ron Gery (Microsoft Developer Network Technology Group), March 20, 1992


OVERVIEW
--------

A DIB (device-independent bitmap) is a format used to define device-independent
bitmaps in various color resolutions. The main purpose of DIBs is to allow
bitmaps to be moved from one device to another (hence, the device-independent
part of the name).
...
A DIB consists of two parts: the bits themselves and a header that describes the
format of the bits. The header contains the color format, a color table, and the
size of the bitmap. The current DIB format supports four color resolutions:
1 bit, 4 bit, 8 bit, and 24 bit. In 1-bit, 4-bit, and 8-bit DIBs, the pixels are
defined by indexes (of the appropriate bit resolution) into the color table;
24-bit pixels are described as 24-bit values, 1 byte each for red, green, and
blue.
...


DEVICE INDEPENDENCE - WHAT'S IT GOOD FOR?
-----------------------------------------

Transferring color bitmaps from one device to another was not possible in
versions of the Microsoft® Windows™ graphical environment earlier than 3.0.
With DIBs, each device displays the image to the ability of its color resolution.
An application can store an image in the DIB format and then display it,
regardless of the output device; an application need no longer create a version
of each image for each type of device.
...

Because the DIB format is publicly defined, an application can manipulate it on
the fly. In fact, an application can build an image without any interaction with
Windows. If Windows lacks a drawing primitive, the application can simulate it
directly into the DIB instead of using the existing graphics device interface
(GDI) primitives.
...


BMP FILE FORMATS
----------------

The file extension of a Windows DIB file is BMP. The file consists of a
BITMAPFILEHEADER structure followed by the DIB itself. Unfortunately, because
the BITMAPFILEHEADER structure is never actually passed to the API, not every
application that generates BMP files fills out the data structure carefully.
To add to this confusion, the "proper" definition of the structure is at odds
with the documentation. Properly, the data structure contains the following
fields:

bfType            A WORD that defines the type of file. It must be 'BM'.
bfSize            A DWORD that specifies the size of the file in bytes.
                  The Microsoft Windows Software Development Kit (SDK)
                  documentation claims otherwise. To be on the safe side, many
                  application calculate their own sizes for reading in a file.
bfReserved1,
bfReserved2       WORDs that must be set to 0.
bfOffBits         A DWORD that specifies the offset from the beginning of the
                  BITMAPFILEHEADER structure to the start of the actual bits.
                  the DIB header immediately follows the file header, but the
                  actual image bits need not be placed next to the headers in
                  the file. The DIB header immediately follows the
                  BITMAPFILEHEADER structure. For a code sample that reads a
                  BMP file, see the sample program.


THE DIB HEADER
--------------

The header actually consists of two adjoining parts: the header proper and
the color table. Both are combined in the BITMAPINFO structure, which is what
all DIB APIs expect.
Windows supports two varieties of headers: BITMAPINFOHEADER and
BITMAPCOREHEADER. If at all possible, applications should use only
BITMAPINFOHEADERs.
...

BITMAPINFOHEADER contains the following fields:

biSize            Should be set to sizeof(BITMAPINFOHEADER). This field defines
                  the size of the header (minus the color table). If a new DIB
                  definition is added, it is identified by a new value for the
                  size. This field is also convenient for calculating a pointer
                  to the color table, which immediately follows the
                  BITMAPINFOHEADER.
biWidth,
biHeight          Define the width and the height of the bitmap in pixels.
                  ...
biPlanes          Should always be 1. All DIB definitions rely on biBitCount
                  for defining the color resolution.
biBitCount        Defines the color resolution (in bits per pixel) of the DIB.
                  Only four values are valid for this field: 1, 4, 8, and 24.
                  ...
biCompression     Specifies the type of compression. Can be one of three values:
                  BI_RGB, BI_RLE4, or BI_RLE8. The most common and useful
                  choice, BI_RGB, defines a DIB in which all is as it seems.
                  Each block of biBitCount bits defines an index (or RGB value
                  for 24-bit versions) into the color table. The other two
                  options specify that the DIB is stored (or will be stored)
                  using either the 4-bit or the 8-bit run length encoding (RLE)
                  scheme that Windows supports. The RLE formats are especially
                  useful for animation applications and also usually compress
                  the bitmap. BI_RGB format is recommended for almost all
                  purposes. RLE versions, although possibly smaller, are slower
                  to decode, not as widely supported, and extremely painful to
                  band properly.
biSizeImage       Contains the size of the bitmap proper in bytes or the value
                  0. A value of 0 indicates that the DIB is of default size.
                  Calculating the size of a bitmap is not hard:
                     biSizeImage=((((biWidth*biBitCount)+31)&~31)>>3)*biHeight.
                  The crazy roundoffs and shifts account for the bitmap being
                  DWORD-aligned at the end of every scanline. When nonzero,
                  this field tells an application how much storage space the
                  DIB's bits need. The biSizeImage field really becomes useful
                  when dealing with an RLE bitmap, the size of which depends
                  on how well the bitmap was encoded. If an RLE bitmap is to
                  be passed around, the biSizeImage field is mandatory.
biXPelsPerMeter,
biYPelsPerMeter   Define application-specified values for the desirable
                  dimensions of the bitmap. This information can be used to
                  maintain the physical dimensions of an image across devices
                  of different resolutions. GDI never touches these fields.
                  When not filled in, they should both be set to 0.
biClrUsed         Provides a way for getting smaller color tables. When this
                  field is set to 0, the number of colors in the color table
                  is based on the biBitCount field (1 indicates 2 colors, 4
                  indicates 16, 8 indicates 256, and 24 indicates no color
                  table). A nonzero value specifies the exact number of colors
                  in the table. So, for example, if an 8-bit DIB uses only 17
                  colors, then only those 17 colors need to be defined in the
                  table, and biClrUsed is set to 17. Of course, no pixel can
                  have an index pointing past the end of the table.
                  ...
                  If nonzero for a 24-bit DIB, it indicates the existence of a
                  color table that the application can use for color reference.
biClrImportant    Specifies that the first x colors of the color table are
                  important to the DIB. If the rest of the colors are not
                  available, the image still retains its meaning in an
                  acceptable manner. biClrImportant is purely for application
                  use; GDI does not touch this value. When this field is set to
                  0, all the colors are important, or, rather, their relative
                  importance has not been computed.


BIT FORMATS
-----------
                  The header defines the format of the bits, but all formats
                  share the following rules:

                    * Every scanline is DWORD-aligned.
                      The scanline is buffered to alignment;
                      the buffering is not necessarily 0.

                    * The scanlines are stored upside down, with the first scan
                      (scan 0) in memory being the bottommost scan in the image
                      ...

________________________________________________________________________________
______________________________________________________________________________*/
