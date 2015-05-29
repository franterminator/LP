@echo off

del *.a

gcc libbmp.c -O2 -c -o libbmp.o
gcc hsl_rgb.c -O2 -c -o hsl_rgb.o

ar r libbmp.a libbmp.o

ar r libHSL.a hsl_rgb.o
del *.o
pause