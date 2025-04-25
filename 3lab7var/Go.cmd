@echo off

if .%USERDOMAIN% == .DESKTOP-PL27T8S goto :savasPC
Rem MIF kompiuteris
path C:\PROGRA~2\Dev-Cpp\MinGW64\bin\;%path%
mingw32-make.exe

goto :toliau

:savasPC
echo mano kompiuteris
make build
build -test > testresult.txt
echo 0.3 > params.txt
echo 1000 >> params.txt
echo 1 >> params.txt
echo 8 >> params.txt
echo 5 >> params.txt
echo 20>> params.txt
echo 5 >> params.txt
echo 10 >> params.txt
echo 15 >> params.txt
echo 25 >> params.txt
echo 0.4 >> params.txt
echo 0.4 >> params.txt
build params.txt -rnd 20 > result1.txt
build > result2.txt
pause

:toliau
echo %USERDOMAIN%
pause