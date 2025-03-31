## Programos Aprašymas

Ši programa sprendžia uždavinį, kaip išdėstyti 8 rikio figūras ant `N x N` šachmatų lentos taip, kad jos kontroliuotų visą lentą. Programa naudoja atkūrimo (`angl. backtracking`) metodą, kad rastų sprendimą, ir palaiko papildomas funkcijas, tokias kaip laiko limitai ir euristiniai režimai. Jei sprendimas randamas, programa išveda lentos konfigūraciją. Jei sprendimas nerandamas arba laikas baigiasi, programa pateikia atitinkamą pranešimą.

## Naudojimas

Programą galima vykdyti naudojant šią komandą:

```bash
PgmName.exe [-|file_name] [-mode [fullSearch|firstMatchSearch|heuristic heuristic_number]] [-timeout milliseconds]
```

### Parametrai:
1. **Įvesties šaltinis**:
   - `-` : Skaityti įvestį iš standartinio įvesties srauto.
   - `file_name` : Skaityti įvestį iš failo, kuriame nurodytas lentos dydis (`N`).

2. **Režimas**:
   - `- mode fullSearch` : Atlikti pilną paiešką, kad būtų rasti visi galimi sprendimai.
   - `- mode firstMatchSearch` : Sustoti radus pirmą sprendimą.
   - `- mode heuristic heuristic_number` : Naudoti konkretų euristinį metodą (šiuo metu neįgyvendinta).

3. **Laiko limitas**:
   - `-timeout milliseconds` : Nustatyti vykdymo laiko limitą. Jei šis laikas baigiasi, programa nutraukia vykdymą ir nurodo, kokią paieškos procentinę dalį pavyko atlikti.

### Pavyzdinės Komandos:
- Skaityti įvestį iš failo ir nustatyti laiko limitą:
  ```bash
  PgmName.exe test1.txt -timeout 5000
  ```
- Skaityti įvestį iš standartinio įvesties srauto:
  ```bash
  PgmName.exe - < test1.txt
  ```

## Įvesties Formatavimas

Įvesties faile turėtų būti vienas sveikasis skaičius `N`, kuris apibrėžia šachmatų lentos dydį (`N x N`).

### Example Input:
```
8
```

## Išvestis

Programa pateikia šią informaciją:
1. Lentos dydis (`N`).
2. Sprendimo lentos konfigūracija, jei sprendimas randamas.
3. Pranešimą apie baigtą laiką, jei laiko limitas buvo viršytas.
4. Pranešimą, jei sprendimo nėra.

### Pavyzdinė Išvestis:
#### Sprendimas Rastas:
```
N = 8
Solution:
B . . . . . . .
. B . . . . . .
. . B . . . . .
. . . B . . . .
. . . . B . . .
. . . . . B . .
. . . . . . B .
. . . . . . . B
```

#### Laiko Limitas Viršytas:
```
N = 8
Timeout occurred.
Program terminated due to timeout. Completed 15.23% of the search.
```

#### Sprendimo Nėra:
```
N = 8
No solution found.
```

## Funkcijos

- **Laiko Limito Valdymas:** Programa nutraukia vykdymą, jei laiko limitas buvo viršytas, ir pateikia atliktos paieškos procentinę dalį.
- **Euristinis režimas:** Programa turi euristinio metodo palaikymą, tačiau jis dar nėra įgyvendintas.
- **Dinaminė Įvestis:** Programa gali skaityti įvestį iš failo arba standartinio įvesties srauto.

## Įgyvendinimo Detalės

- Programa naudoja atkūrimo (angl. backtracking) metodą rikio figūroms išdėstyti ant lentos.
- Funkcija `solve_n_bishops()` atlieka pagrindinę problemos sprendimo logiką.
- Funkcija `handle_timeout()` apskaičiuoja ir pateikia atliktos paieškos procentinę dalį, kai viršijamas laiko limitas.
- Atmintis lentai dinamiškai paskirstoma ir tinkamai išlaisvinama po vykdymo.

## Apribojimai

- Euristinis režimas dar nėra įgyvendintas. Jei jis pasirenkamas, programa pateikia:
  ```
  Euristika dar nerealizuota.
  ```
- Programa daro prielaidą, kad įvestis yra tinkama. Neteisinga arba netinkamai suformatuota įvestis gali sukelti neapibrėžtą elgesį.

## Kaip Kompiliuoti ir Vykdyti

### Kompiliavimas
Naudokite pateiktą `Makefile` failą programai kompiliuoti:
```bash
make
```

### Vykdymas
Vykdykite programą naudodami `go.cmd` skriptą:
```bash
go.cmd
```

Šis skriptas kompiliuoja programą ir paleidžia ją su iš anksto paruoštais testiniais failais (`test1.txt`, `test2.txt`, `test3.txt`).

## Testų Atvejai

### Testo Atvejis 1:
Įvestis (`test1.txt`):
```
8
```
Komanda:
```bash
PgmName.exe - < test1.txt > result1.txt -timeout 5000
```
Tikėtina Išvestis:
```
N = 8
Timeout occurred.
Program terminated due to timeout. Completed x% of the search.
```

### Testo Atvejis 2:
Įvestis (`test2.txt`):
```
7
```
Komanda:
```bash
PgmName.exe - < test2.txt > result2.txt -timeout 5000
```
Tikėtina Išvestis:
```
N = 7
Timeout occurred.
Program terminated due to timeout. Completed x% of the search.
```

### Testo Atvejis 3:
Įvestis (`test3.txt`):
```
9
```
Komanda:
```bash
PgmName.exe - < test3.txt > result3.txt -timeout 5000
```
Tikėtina Išvestis:
```
N = 9
Timeout occurred.
Program terminated due to timeout. Completed x% of the search.
```