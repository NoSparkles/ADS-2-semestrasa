if .%USERDOMAIN% == rober goto :savasPC
Rem MIF kompiuteris
path C:\PROGRA~2\Dev-Cpp\MinGW64\bin\;%path%
mingw32-make.exe
goto :toliau

:savasPC
make
PgmName.exe - < test1.txt > result1.txt -timeout 5000
PgmName.exe - < test2.txt > result2.txt -timeout 5000
PgmName.exe - < test3.txt > result3.txt -timeout 5000

:toliau
PgmName.exe - < test1.txt > result1.txt -timeout 5000
PgmName.exe - < test2.txt > result2.txt -timeout 5000
PgmName.exe - < test3.txt > result3.txt -timeout 5000