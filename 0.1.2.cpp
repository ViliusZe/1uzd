#include <iomanip>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
#include <cctype>
#include <vector>

using namespace std;

// Struktūra, skirta mokinio duomenims laikyti
struct duomenys {
    string v, p;  // Vardas ir pavardė
    vector<int> N;  // Pažymiai, naudojant std::vector<int>
    int paz;  // Pažymių skaičius
    int e;  // Egzamino rezultatas
    double r;  // Galutinis rezultatas
};

// Funkcija tikrinti, ar tekstas (vardas ar pavardė) susideda tik iš raidžių
bool tikrintiVardaPavarde(const string &tekstas) {
    for (char c : tekstas) {
        if (!isalpha(c)) return false;  // Jei yra ne raidė, grąžina klaidą
    }
    return true;
}

// Funkcija, skaičiuojanti vidurkį
double vid(const vector<int>& N) {  // Naudojama std::vector<int> vietoj masyvo
    double sum = 0;
    for (int i = 0; i < N.size(); i++) {
        sum += N[i];  // Sudedame visus pažymius
    }
    return N.size() > 0 ? sum / N.size() : 0;  // Grąžiname vidurkį, jei yra pažymių
}

// Funkcija, skaičiuojanti mediana
double mediana(vector<int>& N) {  // Naudojama std::vector<int> vietoj masyvo
    sort(N.begin(), N.end());  // Rūšiuojame pažymius
    if (N.size() % 2 != 0) {
        return N[N.size() / 2];  // Jei pažymių skaičius nelyginis, grąžiname vidurinį
    }
    else {
        // Jei pažymių skaičius lyginis, grąžiname dviejų vidurinių elementų vidurkį
        return (N[(N.size() - 1) / 2] + N[N.size() / 2]) / 2.0;
    }
}

// Funkcija, skirta mokinių duomenims įvesti
void skaitymas(vector<duomenys>& M) {  // Naudojame std::vector<duomenys> vietoj dinaminio masyvo
    string testi;
    do {
        duomenys temp;
        do {
            cout << "Įveskite mokinio vardą: ";
            cin >> temp.v;
            if (!tikrintiVardaPavarde(temp.v)) {
                cout << "Neteisingas vardas. Bandykite dar kartą.\n";
            }
        } while (!tikrintiVardaPavarde(temp.v));

        do {
            cout << "Įveskite mokinio pavardę: ";
            cin >> temp.p;
            if (!tikrintiVardaPavarde(temp.p)) {
                cout << "Neteisinga pavardė. Bandykite dar kartą.\n";
            }
        } while (!tikrintiVardaPavarde(temp.p));

        cout << "Įveskite mokinio pažymius (baigti įveskite -1): ";
        temp.paz = 0;
        int pazymys;
        while (true) {
            cin >> pazymys;
            if (pazymys == -1) break;  // Baigia įvesti, kai įvedama -1
            if (pazymys < 1 || pazymys > 10) {
                cout << "Pažymys turi būti tarp 1 ir 10. Bandykite dar kartą: ";
                continue;
            }
            temp.N.push_back(pazymys);  // Pridedame pažymį į vektorių
            temp.paz++;
        }

        do {
            cout << "Įveskite mokinio egzamino rezultatą: ";
            cin >> temp.e;
            if (temp.e < 1 || temp.e > 10) {
                cout << "Egzamino rezultatas turi būti tarp 1 ir 10. Bandykite dar kartą.\n";
            }
        } while (temp.e < 1 || temp.e > 10);

        M.push_back(temp);  // Pridedame mokinį į vektorių

        cout << "Ar norite įvesti dar vieną mokinį? (Taip/Ne): ";
        cin >> testi;
    } while (testi == "Taip" || testi == "taip");
}

// Funkcija, skaičiuojanti galutinius rezultatus (vidurkį arba medianą)
void skaiciavimas(vector<duomenys>& M, int pasirinkimas) {  // Naudojame std::vector<duomenys> vietoj masyvo
    for (int i = 0; i < M.size(); i++) {
        if (pasirinkimas == 1) {
            M[i].r = vid(M[i].N) * 0.4 + M[i].e * 0.6;  // Skaičiuojame vidurkį
        } else {
            M[i].r = mediana(M[i].N) * 0.4 + M[i].e * 0.6;  // Skaičiuojame medianą
        }
    }
}

// Funkcija, skirta išvesti galutinius rezultatus
void rasymas(const vector<duomenys>& M) {  // Naudojame std::vector<duomenys> vietoj masyvo
    cout << left << setw(13) << setfill(' ') << "Pavardė" << left << setw(13) << "Vardas" << "Galutinis" << endl;
    cout << setw(40) << setfill('-') << "-" << endl;
    for (int i = 0; i < M.size(); i++) {
        cout << left << setw(13) << setfill(' ') << M[i].p << left << setw(13) << M[i].v << fixed << setprecision(2) << M[i].r << endl;
    }
}

int main() {
    vector<duomenys> M;  // Naudojame std::vector<duomenys> vietoj dinaminio masyvo
    int pasirinkimas;

    cout << "Jei norima skaiciuoti mokinio vidurkį, įveskite 1, jei medianą - 0:" << endl;
    cin >> pasirinkimas;

    skaitymas(M);
    skaiciavimas(M, pasirinkimas);
    rasymas(M);

    return 0;
}
