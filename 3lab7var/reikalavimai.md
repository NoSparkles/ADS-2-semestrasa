# 3-as lab. darbas

7. Poliklinika (ADT: eilė, ilgas sveikas skaičius). Procesas 1: poliklinikoje dirba tik įvairių sričių specialistai, pacientas kreipiasi į specialistą savo nuožiūra, šis arba pacientą pagydo, arba pasiunčia pas tą specialistą, kuris gali pacientą pagydyti, arba informuoja pacientą, kad šis sveikas. Procesas 2: pacientai gali kreipiasi tik į apylinkės gydytoją, kuris pasiunčia pas tą specialistą, kuris gali pacientą pagydyti, arba informuoja pacientą, kad šis sveikas. Patyrinėkime, kiek apylinkės gydytojų poliklinikai tikslinga turėti ekonominiu požiūriu (jų atlyginimas mažesnis nei specialistų ir jie žymiai greičiau priima sprendimą) ir kaip tai paveiks pacientų pasitenkinimą (minimalus, vidutinis ir maksimalus pilno aptarnavimo laikas). Visi kiti rodikliai, nuo kurių priklauso procesas, įvedami kaip programos parametrai.

Atliktame darbe turėtų būti `PSP.xlsx`, kuriame yra lakštai (*sheets*) `LFF`, `PDF`, `DVF`, `PPS`,`DTS` ir `DFF`. `DTS` ir `DFF` gali būti užpildyti nepilnai, ar iš viso neužpildyti, tačiau užpildymui tinkamos lentelės -- privalomos.

`ReadMe.md` -- trumpas darbo apibūdinimas. Pradžioje turi būti aiškiai nurodyta koks (kokie) ADT darbe panaudoti, iš kur jie paimti (iš dėstytojo, ar studento tinklalapio), kiek defektų juose rasta, toliau varianto sąlyga, toliau -- kaip įgyvendinta bendroji kompetencija **bendravimas ir bendradarbiavimas**, toliau -- savo nuožiūra.

`Go.cmd` -- komandų failas darbo sutransliavimui ir įvykdymui.

`Makefile` -- transliavimo make failas.

## ReadMe.md

Iliustruojančių paveikslėlių kopijuoti į darbą nereikia nereikia. Užtenka `![kas iliustruojama](kur radote)`.

## Go.cmd arba Go.bat

Reikia parodyti, kad fakultetinis PC, kažkuo skiriasi nuo asmeninio, pvz.

```cmd
if .%USERDOMAIN% == .SavasPC goto :savasPC
Rem MIF kompiuteris
path C:\PROGRA~2\Dev-Cpp\MinGW64\bin\;%path%
mingw32-make.exe
goto :toliau

:savasPC
make

:toliau
echo 500 modeliavimo laikas > params.txt
echo 5   kasų skaičius >> params.txt
echo 50  kliento atėjimo tikimybė (%) >> params.txt
echo 40  maksimalus kliento apsipirkimo laikas >> params.txt
echo 10  maksimalus kliento aptarnavimo prie kasos laikas >> params.txt
PgmName.exe params.txt -rnd 50 > result1.txt
echo 999 modeliavimo laikas > PgmName.cfg
echo 10  kasų skaičius >> PgmName.cfg
echo 40  kliento atėjimo tikimybė (%) >> PgmName.cfg
echo 50  maksimalus kliento apsipirkimo laikas >> PgmName.cfg
echo 20  maksimalus kliento aptarnavimo prie kasos laikas >> PgmName.cfg
PgmName.exe > result2.txt
```

Jeigu programai nenurodyti parametrų failo, programa per `argv[0]` turi surasti savo vardą, ir `.exe` pakeisti `.cfg`, t.y.\
`PgmName.exe PgmName.cfg > result.txt` turi būti ekvivalentus\
`PgmName.exe > result.txt`

Parametras `-rnd 50` nurodo kokia reik6me (`50`) reikia inicializuoti pseudo-atsitiktinių skaičių daviklį. Jeigu parametras nenurodytas, pseudo-atsitiktinių skaičių daviklis inicijuojamas `time()` reikšme. Abiem atvejais programa turi išvesti inicijuojamą reikšmę, kad būtų aišku kaip atkartoti programos rezultatus.

## Makefile

Iš esmės **transliavimo make failas**, todėl visokie kitokie **make failai** (tipo, šiukšlių išvalymui, sutransliuotos programos vykdymas, etc.) tinkami tik į `KaipSau` darbo direktoriją.

Šiame faile reikia parodyti supratimą, jog dalį parašytų funkcijų galima panaudoti ir kituose darbo variantuose, ir/ar to tipo uždavinių sprendime, todėl tokias funkcijas reikia transliuoti atskirai, nuo programos, pvz.:

```makefile
PgmName.exe : main.c fn_set.h fn_set.o
	gcc -std=c99 -o PgmName.exe main.c fn_set.o

fn_set.o : fn_set.c fn_set.h
	gcc -c -std=c99 fn_set.c
```
