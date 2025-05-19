@echo off
if .%USERDOMAIN% == ".rober" goto :savasPC
Rem MIF kompiuteris
path C:\PROGRA~2\Dev-Cpp\MinGW64\bin\;%path%
mingw32-make.exe
goto :toliau

:savasPC
make
main.exe < input1.txt > output1.txt
main.exe input2.txt > output2.txt

:toliau
main.exe < input1.txt > output1.txt
main.exe input2.txt > output2.txt
