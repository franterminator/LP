@echo off
color F0
cls

set var=0

if exist sub1.c (
	gcc sub1.c -c -o sub1.o
	set /a var=%var%+1
) else	(
	color 02
	cls
	echo el archivo sub1.c no se encuentra)

if exist sub2.c (
	gcc sub2.c -c -o sub2.o
	set /a var=%var%+1
) else	(
	color 02
	cls
	echo el archivo sub2.c no se encuentra)

if exist sub3.c (
	gcc sub3.c -c -o sub3.o
	set /a var=%var%+1
) else	(
	color 02
	cls
	echo el archivo sub3.c no se encuentra)

if exist sub4.c (
	gcc sub4.c -c -o sub4.o
	set /a var=%var%+1
) else	(
	color 02
	cls
	echo el archivo sub4.c no se encuentra)

if exist prog.c (
	gcc prog.c -c -o prog.o
	set /a var=%var%+1
) else	(
	color 02
	cls
	echo el archivo sub4.c no se encuentra)


if %var%==5 (
	gcc prog.o sub1.o sub2.o sub3.o sub4.o -o2 -o prog.exe 
	del sub1.o sub2.o sub3.o sub4.o prog.o
) else	(
	color 02
	cls
	echo hubo problemas durante la compilacion de algun archivo)


pause
