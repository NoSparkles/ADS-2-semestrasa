# 2-as lab. darbas

Atliktame darbe turėtų būti `PSP.xlsx`, kuriame yra lakštai (*sheets*) `LFF`, `KPS`, `DTS`, `DFF`. `DTS` ir `DFF` gali būti užpildyti nepilnai, ar iš viso neužpildyti, tačiau užpildymui tinkamos lentelės -- privalomos.

`ReadMe.md` -- trumpas darbo apibūdinimas. Pradžioje varianto sąlyga, toliau -- kaip įgyvendinta bendroji kompetencija **bendravimas ir bendradarbiavimas**, toliau -- savo nuožiūra.

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
PgmName.exe > result0.txt
echo 5 > test1.txt
echo 1 2 3 4 5 >> test1.txt
PgmName.exe < test1.txt > result1.txt
...
```

Kai kuriuose variantuose pasakyta, jog pradiniai duomenys faile, kituose ne. Laikome, jog pradiniai duomenys gali būti tiek standartiniame įvedimo sraute, tiek faile. Programą reikia realizuoti taip, jog\
`PgmName.exe data.txt > result.txt` būtų ekvivalentus\
`PgmName.exe - < data.txt > result.txt`

Nenurodžius parametrų:\
`fprintf(stderr, "Usage: %s [-|failo_vardas] [-mode [fullSearch|firstMatchSearch|heuristic heuristic_number]] [-timeout miliseconds]\n", argv[0]);`

## Makefile

Iš esmės **transliavimo make failas**, todėl visokie kitokie **make failai** (tipo, šiukšlių išvalymui, sutransliuotos programos vykdymas, etc.) tinkami tik į `KaipSau` darbo direktoriją.

Šiame faile reikia parodyti supratimą, jog dalį parašytų funkcijų galima panaudoti ir kituose darbo variantuose, ir/ar to tipo uždavinių sprendime, todėl tokias funkcijas reikia transliuoti atskirai, nuo programos, pvz.:

```makefile
PgmName.exe : main.c fn_set.h fn_set.o
	gcc -std=c99 -o PgmName.exe main.c fn_set.o

fn_set.o : fn_set.c fn_set.h
	gcc -c -std=c99 fn_set.c
```

## Priklausomai nuo darbo varianto

**Variantas 1.**

Testas1: N=4, {1, 2, 3,
4}, M=2, S=5. 

Testas2: N=5, {1,
2, 3, 4, 5}, M=3, S=8. 

Testas3:
N=14, {1, 2, 3, 4, 5, 6, 7, 8,
10, 11, 14, 15, 17, 20}, M=4,
S=15. 

Testas4: N=11, {1, 1, 2, 2,
5, 5, 6, 6, 8, 8, 10}, M=7, S=20.

**Variantas 2.**

Testas1: N=4,
{s~1~=1, s~2~=6, s~3~=3, s~4~=4}.

Testas2: N=5, {s~1~=4, s~2~=2,
s~3~=5, s~4~=1, s~5~=9}. 

Testas3:
N=5, {s~1~=1, s~2~=3, s~3~=3,
s~4~=1, s~5~=5}. 

Testas4: N=10,
{s~1~=9, s~2~=5, s~3~=2, s~4~=1,
s~5~=7, s~6~=2, s~7~=17, s~8~=5,
s~9~=4, s~10~=3}.

**Variantas 3.**

Testas1:
N=4, {s~1~=1, s~2~=1, s~3~=1,
s~4~=1}, {k~1~=2, k~2~=2, k~3~=2,
k~4~=3}, C=3. 

Testas2: N=4,
{s~1~=4, s~2~=3, s~3~=2, s~4~=1},
{k~1~=5, k~2~=4, k~3~=3, k~4~=2},
C=6. 

Testas3: N=5, {s~1~=1,
s~2~=1, s~3~=1, s~4~=1, s~5~=1},
{k~1~=2, k~2~=3, k~3~=4, k~4~=5,
k~5~=6}, C=4. 

Testas4: N=10,
{s~1~=23, s~2~=26, s~3~=20,
s~4~=18, s~5~=32, s~6~=27,
s~7~=29, s~8~=26, s~9~=30,
s~10~=27}, {k~1~=505, k~2~=352,
k~3~=458, k~4~=220, k~5~=354,
k~6~=414, k~7~=498, k~8~=545,
k~9~=473, k~10~=543}, C=67. 

Tai
**kuprinės uždavinys** (angl.
*knapsack problem*),
<https://en.wikipedia.org/wiki/Knapsack_problem>.

**Variantas 4.**

Testas1: N=5, X=1, Y=1;
bandymų 70 624. 

Testas2: N=5,
X=5, Y=1; bandymų 236. 

Testas3:
N=5, X=1, Y=5; bandymų 111 981.

Testas4: N=5, X=2, Y=1; apėjimo
nėra, bandymų 14 635 368.

Testas5: N=6, X=1, Y=1; bandymų 1
985 212. 

Testas6: N=4, X=1, Y=1;
apėjimo nėra, bandymų 17 784.

Tai
**žirgo maršruto uždavinys**
(angl. *knight's tour problem*),
<https://en.wikipedia.org/wiki/Knight%27s_tour>.
Žr. paaiškinimus ir programos
spausdinamą protokolą
<https://klevas.mif.vu.lt/~cyras/AI/konspektas-intelektualios-sistemos.pdf>
p. 15--20.

**Variantas 5.**

Ištirti 3 testais: 

N=8,
7, 9. Žr.
<https://en.wikipedia.org/wiki/Mathematical_chess_problem>.

**Variantas 6.**

Ištirti 3 testais: N=8, 7, 9.\
Žr.
<https://en.wikipedia.org/wiki/Mathematical_chess_problem>,\
<https://stackoverflow.com/questions/36527317/12-dominating-knights-puzzle-backtracking>.

**Variantas 7.**

Ištirti 3 testais: N=8, 7, 9.\
Žr.
<https://en.wikipedia.org/wiki/Mathematical_chess_problem>.

**Variantas 8.**

Trys
testai.

Gerų testų galima prirankioti iš <https://www.dailysudoku.com/sudoku/>.

**Variantas 9.**

Testas1: SEND+MORE=MONEY

Testas2: CRACK+HACK=ERROR.

Testas3: BASE+BALL=GAME 

(nėra sprendinio). Žr.
<https://en.wikipedia.org/wiki/Verbal_arithmetic>.

**Variantas 10.**

Testas1: {1, 1, 1,
1, 1, 1}. 

Testas2: {1, 2, 3, 4,
5, 6, 7, 8, 9}. 

Testas3:
{1, 3, 5, 7, 9, 11, 13, 15, 17}.

**Variantas 11.**

Testas1: { −7, −3, −2, 5, 8} =\>
{ −3, −2, 5}. Spausdinti visus
sprendinius. 

Testas2:
{1, 2, 3, --1}. 

Testas3: {-4, 3,
7, --6, 1, --3}. 

Testas4: {1, 2,
3, 4}.

**Variantas 12.**

Testas1: v={2, 2, 3, 4, 4, 5},
M=10. Dvi dėžės: {2, 3, 5} ir {2,
4, 4}. 

Testas2: v={2, 2, 3, 3,
4}, M=5. Trys dėžės. 

Testas3:
v={2, 2, 2, 5, 5, 5, 6}, M=7.
Keturios dėžės. 

Testas4: v={2, 4,
5, 9}, M=13. Dvi dėžės. 

Testas5:
v={1, 2, 3, 4, 5}, M=9. Dvi
dėžės. 

Testas6: v={1, 2, 3, 4, 5,
6, 7, 9}, M=13. Trys dėžės.

**Variantas 13.**

Testas1: t={2, 1, 2, 1}, d={3, 1,
6, 4}, b={100, 10, 15, 27}.

Testas2: t={1, 1, 1}, d={1, 2,
3}, b={3, 2, 7}. 

Testas3: t={1,
1, 1}, d={3, 3, 2}, b={0, 0, 10}.

Testas4: t={2, 1, 3, 2}, d={1, 1,
5, 2}, b={3, 1, 2, 2}.

Žr.
<http://ggn.dronacharya.info/CSEDept/Downloads/QuestionBank/Even/VI%20sem/ADA/Section-B/job-scheduling1.pdf>.

**Variantas 14.**

Testas1: N=3, M=3; nėra
sprendinio. 

Testas2: N=3, M=4.

Testas3: N=4, M=4; nėra
sprendinio. 

Testas4: N=4, M=6.

Testas5: N=5, M=8. 

Testas6: N=7,
M=10. 

Testas7: N=8, M=10; nėra
sprendinio.\
Žr. *triangular
N-queens problem*,
<http://acmgnyr.org/year2006/g.pdf>.

**Variantas 15.**

Testai: M=3, 4, 5, 6, 7, 8, 9,
10.\
Žr. *triangular N-queens
problem*,
<http://acmgnyr.org/year2006/g.pdf>.

Sprendimas be perrinkimo tinkamas tik `KaipSau` dalyje.

## Nepriklausomai nuo darbo varianto

Programa privalo užsakovui (ne sau!) suprantamai išvesti su kokiais pradiniais duomenimis dirbo ir kas rezultate gavosi. Jei programa baigė darbą dėl `-timeout miliseconds`, išvedime turi būti informacija procentais, kiek perinkimų atlikta.

`heuristic heuristic_number` gali baigtis pranešimu "euristika dar nerealizuota", tačiau, jeigu jau realizuota, `ReadMe.md` turi būti apibrėžta iš kur, kokia, ir be tuščiažodžiavimo.

Galima sugalvoti (surasti) ir geresnių testų, nei čia išvardyti, tuomet `ReadMe.md` turi būti apibrėžta iš kur, kuo geresni, ir be tuščiažodžiavimo.

Programavimas gijomis `#include <pthread.h>` tinkamas tik `KaipSau` dalyje.

Galima pridėti raktą `-verbose`, reiškiantį detalesnį perrinkimo protokolavimą.

Galima pridėti raktą `-of [html|svg|latex|md]` reiškiantį kokiu formatu rezultatai išvedami, ir pan.