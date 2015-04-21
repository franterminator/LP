cls
prompt $G
if exist (del prog1.exe)
gcc prog1.c -o0 -o prog1.exe
if exist (del prog.exe)
gcc prog.c -o0 -o prog.exe

pause
