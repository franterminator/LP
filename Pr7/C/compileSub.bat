prompt $G
color 02
cls

if exist sub1.c (
	gcc sub1.c -o2 -c -o sub1.o
) else (
	echo doesn't exist sub1.c)

if exist sub1.o (
	ar r lib.a sub1.o
	del sub1.o)


if exist sub2.c (
	gcc sub2.c -o2 -c -o sub2.o
) else (
	echo doesn't exist sub2.c)

if exist sub2.o (
	ar r lib.a sub2.o
	del sub2.o)


if exist sub3.c (
	gcc sub3.c -o2 -c -o sub3.o
) else (
	echo doesn't exist sub3.c)

if exist sub3.o (
	ar r lib.a sub3.o
	del sub3.o)


if exist sub4.c (
	gcc sub4.c -o2 -c -o sub4.o
) else (
	echo doesn't exist sub4.c)

if exist sub4.o (
	ar r lib.a sub4.o
	del sub4.o)

pause