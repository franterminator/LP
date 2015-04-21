cls
prompt $G
color F0
if exist ea.exe (del ea.exe)
gcc ea.c -o2 -o ea.exe
if exist eb.exe (del eb.exe)
gcc eb.c -o2 -o eb.exe
pause Compilado con exito