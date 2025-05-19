#include "funkcijos.h"

int main() {
    string failoPavadinimas = "duomenys.txt";
    string isvedimoFailoPavadinimas = "rezultatai.txt";
    vector<duomenys> M;
    char isvestis;
    int pasirinkimas;

    do {
        cout << "Pasirinkite viena is ju:" << endl;
        cout << "1. Įvesti mokinių duomenis" << endl;
        cout << "2. Sugeneruoti tik pažymius" << endl;
        cout << "3. Sugeneruoti visus duomenis" << endl;
        cout << "4. Skaityti duomenis iš failo" << endl;
        cout << "5. Baigti" << endl;
        cin >> pasirinkimas;
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
                cout << "Kur noretumete isvesti duomenis? Jei i faila=f, jei i konsole=k: ";
                cin >> isvestis;
                if (isvestis == 'f' || isvestis == 'F')
                    rasymasIFaila(M);
                else
                    rasymas(M);
                break;
            case 5:
                cout << "Programos pabaiga." << endl;
                break;
            default:
                cout << "Neteisingas pasirinkimas. Bandykite dar kartą." << endl;
                break;
        }
    } while (pasirinkimas != 5);
}
