#include <iostream>
#include <vector>
#include <stdexcept> // reikalinga std::runtime_error
#include "funkcijos.h" // čia yra visų funkcijų deklaracijos

int main() {
    std::vector<duomenys> M; // pagrindinis vektorius, kuriame saugomi studentų duomenys
    string failoPavadinimas = "duomenys.txt"; // numatytas įvesties failas
    string isvedimoFailoPavadinimas = "rezultatai.txt"; // numatytas išvesties failas
    char isvestis; // naudotojo pasirinkimas dėl duomenų išvedimo (failas ar konsolė)
    int pasirinkimas; // meniu pasirinkimas

    try {
        do {
            // Meniu parinkčių atvaizdavimas
            std::cout << "Pasirinkite viena is ju:" << std::endl;
            std::cout << "1. Įvesti mokinių duomenis" << std::endl;
            std::cout << "2. Sugeneruoti tik pažymius" << std::endl;
            std::cout << "3. Sugeneruoti visus duomenis" << std::endl;
            std::cout << "4. Skaityti duomenis iš failo" << std::endl;
            std::cout << "5. Atlikti testavimus su vector decode ir list" << std::endl;
            std::cout << "6. Generuoti testinius failus" << std::endl;
            std::cout << "7. Analizuoti pasirinktą sugeneruotą failą" << std::endl;
            std::cout << "8. Atlikti analizės tyrimą" << std::endl;
            std::cout << "9. Atlikti analizės tyrimą (Strategija 2)\n";
            std::cout << "10. Atlikti analizės tyrimą (Strategija 3)\n";
            std::cout << "11. Baigti" << std::endl;

            std::cin >> pasirinkimas;
            if (std::cin.fail()) throw std::runtime_error("Neteisingas įvesties formatas."); // Įvesties klaidų patikra
            M.clear(); // išvalomi senieji duomenys

            switch (pasirinkimas) {
            case 1:
                // Naudotojo rankinė duomenų įvestis
                skaitymas(M);
                skaiciavimas(M, gautiPasirinkima());
                rasymas(M);
                break;
            case 2:
                // Tik atsitiktinis pažymių generavimas
                generuotiPazymius(M);
                break;
            case 3:
                // Pilnas atsitiktinis duomenų generavimas
                generuotiVardusPavardesIrPazymius(M);
                skaiciavimas(M, gautiPasirinkima());
                rasymas(M);
                break;
            case 4:
                // Duomenų nuskaitymas iš failo
                skaitymasIsFailo(M, failoPavadinimas);
                skaiciavimas(M, gautiPasirinkima());
                std::cout << "Kur noretumete isvesti duomenis? Jei i faila=f, jei i konsole=k: ";
                std::cin >> isvestis;
                if (isvestis == 'f' || isvestis == 'F') {
                    rasymasIFaila(M); // išvestis į failą
                }
                else {
                    rasymas(M); // išvestis į konsolę
                }
                break;
            case 5: {
                // Testavimų vykdymas naudojant skirtingus konteinerius
                std::vector<std::string> failai = {
                   "studentai_1k.txt", "studentai_10k.txt", "studentai_100k.txt",
                   "studentai_1mln.txt", "studentai_10mln.txt"
                };
                for (const auto& failas : failai) {
                    testuotiVector(failas);
                    testuotiList(failas);
                    testuotiDeque(failas);
                }
                break;
            }
            case 6:
                // Pasirinkto dydžio testinių failų generavimas
                generuotiPasirinktaFaila();
                break;
            case 7:
                // Vieno failo analizė (tikriausiai atvaizduoja laikus)
                analizuotiPasirinktaFaila();
                break;
            case 8:
                // Visų strategijų analizė (strategija 1)
                atliktiAnalize();
                break;
            case 9:
                // Strategija 2 analizė (šalinimas iš kolekcijos)
                atliktiAnalizeStrategija2();
                break;
            case 10:
                // Strategija 3 analizė (naudojama std::partition)
                atliktiAnalizeStrategija3();
                break;
            case 11:
                // Programos pabaiga
                std::cout << "Programos pabaiga." << std::endl;
                return 0;
            default:
                // Jei įvesta neteisinga reikšmė
                std::cout << "Neteisingas pasirinkimas. Bandykite dar kartą." << std::endl;
                break;
            }
        } while (pasirinkimas != 5); // ciklas tęsiamas, kol nepasirinkta 5 (nors gal turėtų būti != 11?)
    }
    catch (const std::runtime_error& e) {
        std::cerr << "Įvyko klaida: " << e.what() << std::endl; // išvedama klaidos žinutė
    }

    return 0;
}
