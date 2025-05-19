#include <iostream>
#include <vector>
#include <stdexcept> // reikalinga std::runtime_error
#include "funkcijos.h"

int main() {
    std::vector<duomenys> M;
    string failoPavadinimas = "duomenys.txt";
    string isvedimoFailoPavadinimas = "rezultatai.txt";
    char isvestis;
    int pasirinkimas;

    try {
        do {
            std::cout << "Pasirinkite viena is ju:" << std::endl;
            std::cout << "1. Įvesti mokinių duomenis" << std::endl;
            std::cout << "2. Sugeneruoti tik pažymius" << std::endl;
            std::cout << "3. Sugeneruoti visus duomenis" << std::endl;
            std::cout << "4. Skaityti duomenis iš failo" << std::endl;
            std::cout << "5. Baigti" << std::endl;
            std::cout << "6. Generuoti testinius failus" << std::endl;

            std::cin >> pasirinkimas;
            if (std::cin.fail()) throw std::runtime_error("Neteisingas įvesties formatas.");
            M.clear();

            switch (pasirinkimas) {
                case 1:
                    skaitymas(M);
                    skaiciavimas(M, gautiPasirinkima());
                    rasymas(M);
                    break;
                case 2:
                    generuotiPazymius(M);
                    break;
                case 3:
                    generuotiVardusPavardesIrPazymius(M);
                    skaiciavimas(M, gautiPasirinkima());
                    rasymas(M);
                    break;
                case 4:
                    skaitymasIsFailo(M, failoPavadinimas);
                    skaiciavimas(M, gautiPasirinkima());
                    std::cout << "Kur noretumete isvesti duomenis? Jei i faila=f, jei i konsole=k: ";
                    std::cin >> isvestis;
                    if (isvestis == 'f' || isvestis == 'F') {
                        rasymasIFaila(M);
                    } else {
                        rasymas(M);
                    }
                    break;
                case 5:
                    std::cout << "Programos pabaiga." << std::endl;
                    break;
                case 6:
                    generuotiVisusFailus();
                    break;
                default:
                    std::cout << "Neteisingas pasirinkimas. Bandykite dar kartą." << std::endl;
                    break;
            }
        } while (pasirinkimas != 5);
    }
    catch (const std::runtime_error& e) {
        std::cerr << "Įvyko klaida: " << e.what() << std::endl;
    }

    return 0;
}
