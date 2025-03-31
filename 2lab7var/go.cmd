if .%USERDOMAIN% == rober goto :savasPC
Rem MIF kompiuteris
path C:\PROGRA~2\Dev-Cpp\MinGW64\bin\;%path%
mingw32-make.exe
goto :toliau

:savasPC
make

:toliau
PgmName.exe - < test1.txt > result1.txt
PgmName.exe - < test2.txt > result2.txt
PgmName.exe - < test3.txt > result3.txt