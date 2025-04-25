# Poliklinikos pacientų srautų simuliacija

## Įvadas
Ši programa simuliuoja poliklinikos pacientų aptarnavimą, analizuodama du skirtingus procesus:

1. **Procesas 1:** Pacientai gali kreiptis tiesiogiai į specialistą. Jei specialistas negali jų gydyti, jie nukreipiami pas kitą specialistą arba informuojami, kad yra sveiki.
2. **Procesas 2:** Pacientai pirmiausia kreipiasi į apylinkės gydytoją, kuris gali juos gydyti arba nukreipti pas specialistą.

Programa analizuoja pacientų pasitenkinimą ir ekonominį efektyvumą remiantis įvestais parametrais.

---

## Įvesties parametrai
Šie parametrai naudojami simuliacijai:

| Parametras                     | Tipas  | Aprašymas |
|--------------------------------|-------|-------------|
| `arrival_probability`          | float | Tikimybė, kad kiekvieną laiko momentą atvyks naujas pacientas (0-1) |
| `simulation_duration`          | int   | Simuliacijos trukmė (laiko vienetais) |
| `local_doctor_count`           | int   | Apylinkės gydytojų skaičius |
| `specialist_count`             | int   | Specialistų skaičius |
| `local_doctor_salary`          | int   | Apylinkės gydytojo atlyginimas |
| `specialist_salary`            | int   | Specialisto atlyginimas |
| `local_doctor_decision_min`    | int   | Minimali diagnozavimo trukmė pas apylinkės gydytoją |
| `local_doctor_decision_max`    | int   | Maksimali diagnozavimo trukmė pas apylinkės gydytoją |
| `specialist_decision_min`      | int   | Minimali diagnozavimo trukmė pas specialistą |
| `specialist_decision_max`      | int   | Maksimali diagnozavimo trukmė pas specialistą |
| `prob_cured_directly`          | float | Tikimybė, kad pacientas bus iškart išgydytas |
| `prob_referred`                | float | Tikimybė, kad pacientas bus nukreiptas pas kitą gydytoją |

---

## Išvesties statistika
Po simuliacijos programa pateikia:
- **Naudotas atsitiktinis skaičius sėjimui**
- **Bendras pacientų skaičius**
- **Išgydytų pacientų skaičius**
- **Vidutinis laukimo laikas**
- **Maksimalus ir minimalus laukimo laikas**
- **Pacientų skaičius, aptarnautų apylinkės gydytojų**
- **Pacientų skaičius, aptarnautų specialistų**
- **Bendra gydymo kaina**
- **Pacientų, likusių eilėje, skaičius**

---

## Naudojimo pavyzdžiai

### 1. Paleisti simuliaciją su numatytais parametrais:
```sh
./build.exe
```

### 2. Paleisti simuliaciją su numatytais parametrais:
```sh
./build.exe build.cfg
```
arba
```sh
./build.exe params.txt
```

### 3. Paleisti testinius scenarijus:
```sh
./build.exe -test
```

### 4. Paleisti simuliaciją su fiksuotu atsitiktiniu skaičiumi
```sh
./build.exe -rnd 42
```

## Pavyzdinė išvestis

```
Random number used for seeding: 42

Total patients: 100
Cured patients: 80
Average time in system: 12.4
Local doctor visits: 60
Specialist visits: 40
Total cost: 5000
Patients still in queue: 5
```

---

## Pastabos
- Jei nepateikiamas failo pavadinimas, programa automatiškai bandys nuskaityti parametrus iš `main.cfg`.
- `-test` paleidžia keletą įmontuotų testinių scenarijų.
- Atsitiktinę generaciją galima kontroliuoti per `-rnd` parametrą, nustatant fiksuotą atsitiktinį skaičių.
