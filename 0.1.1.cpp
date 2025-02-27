#include <iomanip>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
#include <cctype>
using namespace std;

struct duomenys {
    string v, p;
    int *N;
    int paz;
    int e;
    double r;
};

bool tikrintiVardaPavarde(const string &tekstas) {
    for (char c : tekstas) {
        if (!isalpha(c)) return false;
    }
    return true;
}

double vid(int N[], int paz) {
    double sum = 0;
    for (int i = 0; i < paz; i++) {
        sum += N[i];
    }
    return paz > 0 ? sum / paz : 0;
}

double mediana(int N[], int paz) {
    sort(N, N + paz);
    if (paz % 2 != 0) {
        return N[paz / 2];
    }
    else {
        return (N[(paz - 1) / 2] + N[paz / 2]) / 2.0;
    }
}

void skaitymas(duomenys *&M, int &mokSk) {
    string testi;
    do {
        duomenys temp;
        do {
            cout << "Iveskite mokinio varda: ";
            cin >> temp.v;
            if (!tikrintiVardaPavarde(temp.v)) {
                cout << "Neteisingas vardas. Bandykite dar karta.\n";
            }
        } while (!tikrintiVardaPavarde(temp.v));
        
        do {
            cout << "Iveskite mokinio pavarde: ";
            cin >> temp.p;
            if (!tikrintiVardaPavarde(temp.p)) {
                cout << "Neteisinga pavarde. Bandykite dar karta.\n";
            }
        } while (!tikrintiVardaPavarde(temp.p));

        cout << "Iveskite mokinio pazymius (baigti iveskite -1): ";
        temp.paz = 0;
        temp.N = nullptr;
        int pazymys;
        while (true) {
            cin >> pazymys;
            if (pazymys == -1) break;
            if (pazymys < 1 || pazymys > 10) {
                cout << "Pazymys turi buti tarp 1 ir 10. Bandykite dar karta: ";
                continue;
            }
            int *naujas = new int[temp.paz + 1];
            for (int i = 0; i < temp.paz; i++) {
                naujas[i] = temp.N[i];
            }
            naujas[temp.paz] = pazymys;
            delete[] temp.N;
            temp.N = naujas;
            temp.paz++;
        }

        do {
            cout << "Iveskite mokinio egzamino rezultata: ";
            cin >> temp.e;
            if (temp.e < 1 || temp.e > 10) {
                cout << "Egzamino rezultatas turi buti tarp 1 ir 10. Bandykite dar karta.\n";
            }
        } while (temp.e < 1 || temp.e > 10);

        duomenys *naujasMasyvas = new duomenys[mokSk + 1];
        for (int i = 0; i < mokSk; i++) {
            naujasMasyvas[i] = M[i];
        }
        naujasMasyvas[mokSk] = temp;
        delete[] M;
        M = naujasMasyvas;
        mokSk++;

        cout << "Ar norite ivesti dar viena mokini? (Taip/Ne): ";
        cin >> testi;
    } while (testi == "Taip" || testi == "taip");
}

void skaiciavimas(duomenys M[], int mokSk, int pasirinkimas) {
    for (int i = 0; i < mokSk; i++) {
        if (pasirinkimas == 1) {
            M[i].r = vid(M[i].N, M[i].paz) * 0.4 + M[i].e * 0.6;
        } else {
            M[i].r = mediana(M[i].N, M[i].paz) * 0.4 + M[i].e * 0.6;
        }
    }
}

void rasymas(duomenys M[], int mokSk) {
    cout << left << setw(13) << setfill(' ') << "Pavarde" << left << setw(13) << "Vardas" << "Galutinis" << endl;
    cout << setw(40) << setfill('-') << "-" << endl;
    for (int i = 0; i < mokSk; i++) {
        cout << left << setw(13) << setfill(' ') << M[i].p << left << setw(13) << M[i].v << fixed << setprecision(2) << M[i].r << endl;
        delete[] M[i].N;
    }
}

int main() {
    duomenys *M = nullptr;
    int mokSk = 0;
    int pasirinkimas;

    cout << "Jei norima skaiciuoti mokinio vidurki iveskite 1, jei mediana - 0:" << endl;
    cin >> pasirinkimas;

    skaitymas(M, mokSk);
    skaiciavimas(M, mokSk, pasirinkimas);
    rasymas(M, mokSk);

    delete[] M;
    return 0;
}
