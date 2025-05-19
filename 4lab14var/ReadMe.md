# Grafo transformavimas į medį naudojant paiešką į plotį (BFS)

## Aprašymas
Ši programa sukuria grafą, leidžia jam pridėti kraštines ir konvertuoja jį į medį, naudojant **paiešką į plotį (BFS)**.  
Programa gali priimti įvesties duomenis iš failo arba iš standartinio įvesties srauto (`stdin`), jei failas nenurodytas.

## Naudojimas
Kompiliuokite programą:
```
make
```


Paleiskite su įvesties failu:
```
./main input.txt
```

Arba naudokite standartinį įvestį:

```
./main < input.txt
```

### Pavyzdinė įvestis (`input.txt`)

Pirmas skaičius nurodo viršūnių skaičių, toliau pateikiamos kraštinės tarp jų.

```
7
0 1 
0 2 
1 3 
1 4 
2 5 
2 6
```

### Pavyzdinė išvestis

```
Added: 0 -> 1
Added: 0 -> 2
Added: 1 -> 3
Added: 1 -> 4
Added: 2 -> 5
Added: 2 -> 6

Graph before converting to a tree:

Graph adjacency list:
0: 2 1 
1: 4 3 0 
2: 6 5 0 
3: 1 
4: 1 
5: 2 
6: 2 

BFS tree formation starting from vertex 0:

Tree structure:
0 -> 1
0 -> 2
1 -> 3
1 -> 4
2 -> 5
2 -> 6
```



## Failų struktūra
- `graph.h` – antraštinis failas su struktūros apibrėžimais.
- `graph.c` – funkcijos grafui sukurti, kraštinėms pridėti, BFS vykdyti.
- `main.c` – pagrindinė programa, valdanti grafo kūrimą ir jo transformavimą.
- `Go.cmd` – skriptas, kuris paleidžia programą.
- `Makefile` – skriptas, leidžiantis lengvai kompiliuoti programą.