if .%USERDOMAIN% == rober goto :savasPC
Rem MIF kompiuteris
path C:\PROGRA~2\Dev-Cpp\MinGW64\bin\;%path%
mingw32-make.exe
goto :toliau

:savasPC
make

:toliau
PgmName.exe > result0.txt
echo 5 > test1.txt
echo 1 2 3 4 5 >> test1.txt
PgmName.exe < test1.txt > result1.txt