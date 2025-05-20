@echo off
if .%USERDOMAIN% == ".rober" goto :savasPC
Rem MIF kompiuteris
path C:\PROGRA~2\Dev-Cpp\MinGW64\bin\;%path%
mingw32-make.exe
goto :toliau

:savasPC
echo 7 > input1.txt
echo 0 1 >> input1.txt
echo 0 2 >> input1.txt
echo 1 3 >> input1.txt
echo 1 4 >> input1.txt
echo 2 5 >> input1.txt
echo 2 6 >> input1.txt

echo 8 > input2.txt
echo 0 1 >> input2.txt
echo 0 2 >> input2.txt
echo 1 3 >> input2.txt
echo 1 4 >> input2.txt
echo 2 5 >> input2.txt
echo 2 6 >> input2.txt
echo 3 7 >> input2.txt
echo 4 7 >> input2.txt
echo 5 7 >> input2.txt
echo 6 7 >> input2.txt

make
main.exe < input1.txt > output1.txt
main.exe input2.txt > output2.txt

:toliau
echo 7 > input1.txt
echo 0 1 >> input1.txt
echo 0 2 >> input1.txt
echo 1 3 >> input1.txt
echo 1 4 >> input1.txt
echo 2 5 >> input1.txt
echo 2 6 >> input1.txt

echo 8 > input2.txt
echo 0 1 >> input2.txt
echo 0 2 >> input2.txt
echo 1 3 >> input2.txt
echo 1 4 >> input2.txt
echo 2 5 >> input2.txt
echo 2 6 >> input2.txt
echo 3 7 >> input2.txt
echo 4 7 >> input2.txt
echo 5 7 >> input2.txt
echo 6 7 >> input2.txt

main.exe < input1.txt > output1.txt
main.exe input2.txt > output2.txt
