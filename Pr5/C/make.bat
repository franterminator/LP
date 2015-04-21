:IniMake
@echo off

REM Opciones:
REM
REM    make            : compilar y linkar prog.c y {sub1.c, sub2.c, sub3.c}
REM    make prog       : compilar y linkar prog.c y {sub1.c, sub2.c, sub3.c}
REM    make prog.o     : compilar prog.c
REM    make subs.o     : compilar {sub1.c, sub2.c, sub3.c}
REM    make libsubs.a  : archivar {sub1.o, sub2.o, sub3.o} en libsubs.a
REM    make prog.exe   : linkar prog.o con {sub1.o, sub2.o, sub3.o} o (en su defecto) con libsubs.a

if "%1"==""        goto CompLink
if %1==prog        goto CompLink
if %1==prog.o      goto PComp
if %1==subs.o      goto SComp
if %1==libsubs.a   goto Lib
if %1==prog.exe    goto Link

echo Make-Error: opcion no contemplada.
goto EndMake

:CompLink
REM Compilamos y linkamos  [prog.c sub1.c sub2.c sub3.c -> prog.exe]
if exist prog.c (if exist sub1.c (if exist sub2.c (if exist sub3.c goto DoCompLink)))
echo Make-Error: no existen todos los archivos necesarios: prog.c y {sub1.c, sub2.c, sub3.c}
goto EndMake
:DoCompLink
gcc prog.c sub1.c sub2.c sub3.c -O2 -o prog.exe
goto EndMake

:PComp
REM Compilamos             [prog.c -> prog.o]
if exist prog.c goto DoPComp
echo Make-Error: no existe el archivo prog.c
goto EndMake
:DoPComp
gcc prog.c -c -O2 -o prog.o
goto EndMake

:SComp
REM Compilamos             [sub1.c sub2.c sub3.c -> sub1.o sub2.o sub3.o]
if exist sub1.c (if exist sub2.c (if exist sub3.c goto DoSComp))
echo Make-Error: no existen todos los archivos necesarios: {sub1.c, sub2.c, sub3.c}
goto EndMake
:DoSComp
gcc sub1.c -c -O2 -o sub1.o
gcc sub2.c -c -O2 -o sub2.o
gcc sub3.c -c -O2 -o sub3.o
goto EndMake

:Lib
REM Archivamos             [sub1.o sub2.o sub3.o -> libsubs.a]
if exist sub1.o (if exist sub2.o (if exist sub3.o goto DoLib))
echo Make-Error: no existen todos los archivos necesarios: {sub1.o, sub2.o, sub3.o}
goto EndMake
:DoLib
ar r libsubs.a sub1.o
ar r libsubs.a sub2.o
ar r libsubs.a sub3.o
del sub*.o
goto EndMake

:Link
REM Linkamos               [prog.o sub1.o sub2.o sub3.o -> prog.exe]
REM o (en su defecto)      [prog.o libsubs.a            -> prog.exe]
if exist prog.o (if exist sub1.o (if exist sub2.o (if exist sub3.o goto DoLink)))
if exist prog.o (if exist libsubs.a goto DoLinkLib)
echo Make-Error: no existen los dos archivos necesarios: prog.o y {sub1.o, sub2.o, sub3.o} o libsubs.a
goto EndMake
:DoLink
gcc prog.o sub1.o sub2.o sub3.o -O2 -o prog.exe
del prog.o sub*.o
goto EndMake
:DoLinkLib
REM No recomendable: gcc prog.o -L. -lsubs -O2 -o prog.exe
gcc prog.o libsubs.a -O2 -o prog.exe
del prog.o
goto EndMake


:EndMake
