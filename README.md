# Studentų analizės programa (v1.0)

## Sistemos informacija

* CPU: AMD Ryzen 9 5950X (32 threads)
* RAM: 32 GB G.Skill TridentZ RGB 4800 MHz
* Diskas: Samsung 980 Evo 1TB SSD

---

## Konteinerių palyginimo testai (Strategija 1)

| Failas               | Konteineris | Nuskaitymas (ms) | Ršiavimas (ms) | Skirstymas (ms) |
| -------------------- | ----------- | ---------------- | -------------- | --------------- |
| studentai\_1k.txt    | Vector      | 29               | 6              | 3               |
|                      | List        | 27               | 0              | 1               |
|                      | Deque       | 28               | 7              | 1               |
| studentai\_10k.txt   | Vector      | 301              | 78             | 34              |
|                      | List        | 277              | 2              | 11              |
|                      | Deque       | 285              | 88             | 11              |
| studentai\_100k.txt  | Vector      | 3135             | 864            | 363             |
|                      | List        | 2790             | 29             | 125             |
|                      | Deque       | 2871             | 961            | 133             |
| studentai\_1mln.txt  | Vector      | 31267            | 8053           | 4208            |
|                      | List        | 28108            | 551            | 1325            |
|                      | Deque       | 28832            | 9431           | 1367            |
| studentai\_10mln.txt | Vector      | 327056           | 93312          | 54424           |
|                      | List        | 291258           | 9531           | 20032           |
|                      | Deque       | 298451           | 110825         | 20473           |

> **Išvada:** vidutiniškai `std::list` yra greičiausias konteineris ršiavimui ir skirstymui.

---

## Strategija 2 (su ištrynimu iš pradinio konteinerio)

| Failas               | Konteineris | Nuskaitymas (ms) | Skirstymas (ms) |
| -------------------- | ----------- | ---------------- | --------------- |
| studentai\_1k.txt    | Vector      | 29               | 1               |
|                      | List        | 27               | 1               |
|                      | Deque       | 27               | 1               |
| studentai\_10k.txt   | Vector      | 292              | 18              |
|                      | List        | 272              | 10              |
|                      | Deque       | 271              | 12              |
| studentai\_100k.txt  | Vector      | 3058             | 268             |
|                      | List        | 2740             | 111             |
|                      | Deque       | 2745             | 146             |
| studentai\_1mln.txt  | Vector      | 30286            | 2625            |
|                      | List        | 27650            | 1110            |
|                      | Deque       | 27594            | 1493            |
| studentai\_10mln.txt | Vector      | 201645           | 19889           |
|                      | List        | 181209           | 7939            |
|                      | Deque       | 180959           | 11124           |

---

## Strategija 3 (optimizuota su `std::partition` ir STL algoritmais)

| Failas               | Konteineris | Nuskaitymas (ms) | Skirstymas (ms) |
| -------------------- | ----------- | ---------------- | --------------- |
| studentai\_1k.txt    | Vector      | 30               | 1               |
|                      | List        | 28               | 1               |
|                      | Deque       | 28               | 1               |
| studentai\_10k.txt   | Vector      | 304              | 14              |
|                      | List        | 281              | 12              |
|                      | Deque       | 281              | 17              |
| studentai\_100k.txt  | Vector      | 3170             | 153             |
|                      | List        | 2840             | 132             |
|                      | Deque       | 2852             | 199             |
| studentai\_1mln.txt  | Vector      | 31396            | 1539            |
|                      | List        | 28612            | 1336            |
|                      | Deque       | 28666            | 2013            |
| studentai\_10mln.txt | Vector      | 208377           | 11116           |
|                      | List        | 187002           | 10363           |
|                      | Deque       | 187578           | 15195           |

> **Išvada:** Strategija 3 yra pati efektyviausia daugumai konteinerių, ypač `vector` ir `deque`.

---

## Projekto struktūra

* `main.cpp` – valdymo meniu
* `funkcijos.cpp/.h` – visi įrankiai, duomenų skaitymas, skirstymas ir analizės funkcijos
* `testavimai.cpp` – Strategijos 1–3 realizacijos visiems konteineriams
* `duomenys.txt`, `studentai_*.txt` – testavimo duomenų failai

---

## Paleidimo instrukcija

1. Kompiliuokite naudodami `Makefile` arba `CMakeLists.txt`
2. Paleiskite programą terminale:


./main


3. Pasirinkite norimą analizės punktą (8 – Strategija 1, 10 – Strategija 2, 11 – Strategija 3)

