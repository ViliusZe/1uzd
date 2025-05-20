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
---

## Diegimo instrukcija (naudojant CMake)

### 1. Sukurkite `build` katalogą:

```bash
mkdir build
cd build
```

### 2. Paleiskite `cmake`:

```bash
cmake ..
```

### 3. Sukompiliuokite programą:

```bash
cmake --build .
```

### 4. Paleiskite programą:

```bash
./StudentuAnalize     # Linux/Mac
StudentuAnalize.exe   # Windows
```

> **Pastaba:** Įsitikinkite, kad `duomenys.txt` yra tame pačiame kataloge kaip vykdomasis `.exe`.

### 5. Versiju informacija

#### v0.1

Pridėta galimybė programai veikti su nežinomu:
namų darbų kiekiu (n),
studentų skaičiumi (m).
Įgyvendinti du duomenų saugojimo sprendimai:
naudojant C tipo masyvus (*.cpp failas su masyvų realizacija),
naudojant std::vector konteinerius (atskiras *.cpp failas).
Įdiegta atsitiktinių duomenų generavimo funkcija:
namų darbų bei egzamino balai gali būti generuojami automatiškai.

#### pilna v0.2

Nauja šaka v0.2 (sukurta v0.1 pagrindu):
Visas funkcionalumas iš v0.1 versijos buvo perimtas ir plėtojamas toliau.
Duomenų nuskaitymas iš failo:
Pridėtas palaikymas įkelti studentų duomenis iš teksto failo (kursiokai.txt), naudojant tik std::vector pagrįstą versiją.
Failo struktūra:
Vardas Pavardė ND1 ND2 ... NDn Egz.
Programa automatiškai analizuoja duomenis ir pateikia rezultatą.
Išvesties formatavimas:
Rezultatų išvedimas galimas:
tiesiogiai į ekraną arba
į kitą failą (pagal naudotojo pasirinkimą).
Įgyvendinta lygiuotų stulpelių struktūra, kad rezultatai būtų aiškūs ir tvarkingi.
Rikiavimas pagal pasirinkimą:
Pridėta galimybė rūšiuoti studentų duomenis pagal: vardą, pavardę, galutinį balą (vidurkį), galutinį balą (medianą).
Testavimas su dideliais duomenų failais:
Programa buvo sėkmingai išbandyta su testiniais failais:
Studentai10000.txt
Studentai100000.txt
Studentai1000000.txt

#### v0.3 

Pagrindiniai pakeitimai nuo v0.2:
Sukurta šaka v0.3 (iš v0.2):

Ši versija pradėta kaip v0.2 plėtinys, orientuotas į kodo pertvarkymą ir struktūrinį pagerinimą.
Kodo refaktoringas:

Esama programa pertvarkyta į **modulinę struktūrą:

Keli .cpp failai, skirti skirtingoms funkcijoms (pvz., duomenų nuskaitymui, skaičiavimui, rūšiavimui, išvedimui).

Atitinkami .h (header) failai, kuriuose:

Aprašytos naudotos struct struktūros,
Deklaruotos funkcijos ir naudoti duomenų tipai.
Struktūros (struct) naudojimas:

Kur tikslinga, duomenys apjungti į struktūras
Išimčių valdymas (Exception Handling):

Pridėtas bazinis išimčių valdymas:

Tikrinama failo atidarymo sėkmė.
Gaudomos galimos klaidos skaičių konvertavimo metu.
Įtrauktas try-catch blokas, kad būtų galima tvarkingai apdoroti netikėtumus vykdymo metu.

### v0.4 release

Pagrindiniai pakeitimai nuo v0.3:
Sukurta šaka v0.4 (remiantis optimizuota v0.3 versija):

Perimtas stabilus ir struktūruotas v0.3 kodas.
Pradėtas testavimui ir našumo analizėms skirtas modulis.
Failų generatoriaus sukūrimas:

Sukurta funkcija, kuri automatiškai generuoja testavimo failus pagal šabloną:

VardasNRx PavardeNRx ND1 ND2 ... NDn Egz.

Generuoti failai su šiais įrašų kiekiais:

studentai1k.txt (1 000),
studentai10k.txt (10 000),
studentai100k.txt (100 000),
studentai1mln.txt (1 000 000),
studentai10mln.txt (10 000 000).
Šie failai saugomi kaip archyvas tolimesniems testams.

Studentų skirstymas į dvi kategorijas:

„Vargšiukai“ – galutinis balas < 5.0.

„Kietiakiai“ – galutinis balas ≥ 5.0.

Studentai rūšiuojami į atskirus konteinerius ir išvedami į:

vargsiukai*.txt
kietiakiai*.txt
Programos veikimo spartos tyrimai:

Įdiegti du atskiri testavimo režimai:

Failų generavimo trukmės matavimas:
Matuojamas tik failo sugeneravimo laikas, be vector ar struktūrų – tik tiesioginis rašymas.
Duomenų apdorojimo laiko analizė:
Laiko matavimas suskirstytas į etapus:

Failo nuskaitymas
Studentų rūšiavimas į dvi grupes
Išvedimas į atskirus failus
Bendra viso proceso trukmė
Laiko matavimui naudotas std::chrono biblioteka.

#### v1.0 pre relase 

Pagrindiniai pakeitimai nuo v0.4:
Sukurta šaka v1.0 (remiantis v0.4):

Pridėtas konteinerių spartos tyrimo funkcionalumas, skirtas galutinio programos veikimo efektyvumui įvertinti.
Trys atskiros versijos pagal konteinerius:

Tyrimui naudoti skirtingi STL konteineriai:

std::vector<Studentas>
std::list<Studentas>
std::deque<Studentas>
Tiksliai išmatuoti žingsniai kiekvienam konteineriui:

*Duomenų nuskaitymo iš failo į pasirinktą konteinerį laikas.
*Rūšiavimo (sort()) trukmė pagal pasirinktą kriterijų.
*Studentų padalijimo į dvi kategorijas trukmė:

„Vargšiukai“ (galutinis < 5.0),
„Kietiakiai“ (galutinis ≥ 5.0).
Tyrimas atliktas su šiais failais:

studentai1k.txt
studentai10k.txt
studentai100k.txt
studentai1mln.txt
studentai10mln.txt
Tyrimų rezultatai dokumentuoti README.md faile:

Pateikti tikslūs veikimo laikai (ms/s) kiekvienam konteineriui ir kiekvienam įrašų kiekiui.

Pridėti sistemos parametrai, kurioje vyko testavimas:

CPU: AMD Ryzen 9 5950X (32 threads)
RAM: 32 GB G.Skill TridentZ RGB 4800 MHz
Diskas: Samsung 980 Evo 1TB SSD
* Pateikta išvada, **kuris konteineris efektyviausias** pagal konkretų žingsnį ar įrašų kiekį.

#### v1.0 release
* Pagrindiniai pakeitimai nuo pradinės v1.0 versijos:
Studentų skirstymo į dvi kategorijas strategijų analizė:

⚙ Įgyvendintos ir ištestuotos 3 skirstymo strategijos:
 1 strategija – Dviejų naujų konteinerių kūrimas:
Kiekvienas studentas nukopijuojamas į atitinkamą naują konteinerį („vargšiukai“ arba „kietiakiai“).

Trūkumai: Dvigubas atminties naudojimas.

Nauda: Paprasta įgyvendinti, nereikalauja modifikuoti pirminio konteinerio.

 2 strategija – Vieno naujo konteinerio kūrimas + šalinimas:
Tik „vargšiukai“ nukopijuojami į naują konteinerį, iš pradinio pašalinami.

Likę duomenys pradiniame konteineryje – „kietiakiai“.

Pranašumas: Efektyvesnis atminties naudojimas.

Problema: std::vector atveju dažni erase() kvietimai lėti, ypač su dideliais duomenimis.

 3 strategija – Optimizuota skirstymo versija:
Įgyvendinta naudojant std::partition ir std::stable_partition.

std::partition padalina vektorių į dvi dalis pagal predikatą (galutinis balas < 5.0).

std::copy / std::move naudojami greitam nukopijavimui.

Testavimo rezultatai:
Tyrimas atliktas su šiais STL konteineriais:

std::vector<Studentas>

std::list<Studentas>

std::deque<Studentas>

Kiekviena strategija išmatuota šiuose etapuose:

Duomenų nuskaitymas iš failo

Studentų skirstymas į dvi kategorijas

Laiko matavimas kiekvienam žingsniui naudojant std::chrono

Testuoti failų dydžiai:

studentai1k.txt

studentai10k.txt

studentai100k.txt

studentai1mln.txt

studentai10mln.txt

Testavimo rezultatai (laikai milisekundėmis) pateikti lentelėse README faile.

Greičiausia strategija su std::vector – 3 strategija (su partition)

std::list – gerai veikia su 2 strategija 

std::deque – našumas tarp vector ir list, bet neprilygsta optimizuotam vector variantui su partition

Atminties naudojimo efektyvumu laimi 2 ir 3 strategijos

Rekomenduojama naudoti STL algoritmus, kai tik įmanoma – geresnis veikimo laikas ir paprastesnis kodas

## Autorius

Vilius Zeigis
