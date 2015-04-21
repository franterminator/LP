cls
prompt $G
color F0
if exist prog.exe (del prog.exe)
gcc prog.c -o2 -o prog.exe
pause Presione una tecla para ejecutar el programa
cls
prog.exe
pause