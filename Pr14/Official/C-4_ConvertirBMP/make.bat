@echo off
del *.o *.exe
set file=totxt
gcc %file%.c -O2 -c -o %file%.o
gcc %file%.o ../C-Lib/libbmp.a -O2 -o %file%.exe
del *.o

set file=tobmp
gcc %file%.c -O2 -c -o %file%.o
gcc %file%.o ../C-Lib/libbmp.a -O2 -o %file%.exe
del *.o

pause