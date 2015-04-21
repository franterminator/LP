prompt $G
color F0
cls
if exist lib.a (
	gcc prog.c -o2 -c -o prog.o
	gcc prog.o lib.a -o2 -o prog.exe)
	
pause Pulse cualquier tecla para ejecutar el programa
cls
prog.exe