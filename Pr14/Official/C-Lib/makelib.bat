@echo off
del *.a
gcc libbmp.c -O2 -c -o libbmp.o
ar r libbmp.a libbmp.o
del *.o
pause