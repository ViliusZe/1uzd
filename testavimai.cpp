#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <list>
#include <deque>
#include <numeric>
#include <chrono>
#include <algorithm> // reikalinga sort funkcijai
#include "funkcijos.h"

using namespace std;
using namespace std::chrono;

// Funkcija testuoja vector konteinerio našumą: nuskaitymą, rūšiavimą ir skirstymą
void testuotiVector(const string& failas) {
    vector<duomenys> visi, vargsiukai, kietiakiai; // pagrindinis sąrašas ir dvi grupės

    ifstream in(failas); // atidaromas failas
    string eilute;
    getline(in, eilute); // praleidžiama antraštės eilutė

    // Laikmatis: pradeda skaičiuoti nuskaitymo trukmę
    auto start_nuskaitymo = high_resolution_clock::now();

    // Eilučių nuskaitymas
    while (getline(in, eilute)) {
        stringstream ss(eilute);
        duomenys s;
        ss >> s.v >> s.p; // vardas ir pavardė
        int paz;
        while (ss >> paz) s.N.push_back(paz); // pažymiai
        s.e = s.N.back(); s.N.pop_back(); // paskutinis pažymys – egzaminas
        s.paz = s.N.size();
        s.r = 0.4 * accumulate(s.N.begin(), s.N.end(), 0.0) / s.paz + 0.6 * s.e; // galutinis balas
        visi.push_back(s); // saugomas objektas
    }
    auto end_nuskaitymo = high_resolution_clock::now();

    // Laikmatis: rūšiavimo pradžia
    auto start_rusiavimo = high_resolution_clock::now();
    sort(visi.begin(), visi.end(), [](const duomenys& a, const duomenys& b) { return a.r < b.r; }); // rūšiuojama
    auto end_rusiavimo = high_resolution_clock::now();

    // Laikmatis: skirstymo pradžia
    auto start_skirstymo = high_resolution_clock::now();
    for (const auto& s : visi) {
        if (s.r < 5.0) vargsiukai.push_back(s); // blogai besimokantys
        else kietiakiai.push_back(s); // geri studentai
    }
    auto end_skirstymo = high_resolution_clock::now();

    // Išvedami laikai
    cout << "\n[Vector] Failas: " << failas << "\n";
    cout << "Nuskaitymas: " << duration_cast<milliseconds>(end_nuskaitymo - start_nuskaitymo).count() << " ms\n";
    cout << "Rūšiavimas:   " << duration_cast<milliseconds>(end_rusiavimo - start_rusiavimo).count() << " ms\n";
    cout << "Skirstymas:   " << duration_cast<milliseconds>(end_skirstymo - start_skirstymo).count() << " ms\n";
}
//Testuoti List veikia taippat kaip ir Vektor tik list naudoja .sort(0 vietoje std::sort()
void testuotiList(const string& failas) {
    list<duomenys> visi, vargsiukai, kietiakiai;
    ifstream in(failas);
    string eilute;
    getline(in, eilute);

    auto start_nuskaitymo = high_resolution_clock::now();
    while (getline(in, eilute)) {
        stringstream ss(eilute);
        duomenys s;
        ss >> s.v >> s.p;
        int paz;
        while (ss >> paz) s.N.push_back(paz);
        s.e = s.N.back(); s.N.pop_back();
        s.paz = s.N.size();
        s.r = 0.4 * accumulate(s.N.begin(), s.N.end(), 0.0) / s.N.size() + 0.6 * s.e;
        visi.push_back(s);
    }
    auto end_nuskaitymo = high_resolution_clock::now();

    auto start_rusiavimo = high_resolution_clock::now();
    visi.sort([](const duomenys& a, const duomenys& b) { return a.r < b.r; });
    auto end_rusiavimo = high_resolution_clock::now();

    auto start_skirstymo = high_resolution_clock::now();
    for (const auto& s : visi) {
        if (s.r < 5.0) vargsiukai.push_back(s);
        else kietiakiai.push_back(s);
    }
    auto end_skirstymo = high_resolution_clock::now();

    cout << "\n[List] Failas: " << failas << "\n";
    cout << "Nuskaitymas: " << duration_cast<milliseconds>(end_nuskaitymo - start_nuskaitymo).count() << " ms\n";
    cout << "Rusiavimas:   " << duration_cast<milliseconds>(end_rusiavimo - start_rusiavimo).count() << " ms\n";
    cout << "Skirstymas:   " << duration_cast<milliseconds>(end_skirstymo - start_skirstymo).count() << " ms\n";
}
//Testuoti Deque veikia taippat kaip ir Vektor bet tinka dviem galams
void testuotiDeque(const string& failas) {
    deque<duomenys> visi, vargsiukai, kietiakiai;
    ifstream in(failas);
    string eilute;
    getline(in, eilute);

    auto start_nuskaitymo = high_resolution_clock::now();
    while (getline(in, eilute)) {
        stringstream ss(eilute);
        duomenys s;
        ss >> s.v >> s.p;
        int paz;
        while (ss >> paz) s.N.push_back(paz);
        s.e = s.N.back(); s.N.pop_back();
        s.paz = s.N.size();
        s.r = 0.4 * accumulate(s.N.begin(), s.N.end(), 0.0) / s.N.size() + 0.6 * s.e;
        visi.push_back(s);
    }
    auto end_nuskaitymo = high_resolution_clock::now();

    auto start_rusiavimo = high_resolution_clock::now();
    sort(visi.begin(), visi.end(), [](const duomenys& a, const duomenys& b) { return a.r < b.r; });
    auto end_rusiavimo = high_resolution_clock::now();

    auto start_skirstymo = high_resolution_clock::now();
    for (const auto& s : visi) {
        if (s.r < 5.0) vargsiukai.push_back(s);
        else kietiakiai.push_back(s);
    }
    auto end_skirstymo = high_resolution_clock::now();

    cout << "\n[Deque] Failas: " << failas << "\n";
    cout << "Nuskaitymas: " << duration_cast<milliseconds>(end_nuskaitymo - start_nuskaitymo).count() << " ms\n";
    cout << "Rusiavimas:   " << duration_cast<milliseconds>(end_rusiavimo - start_rusiavimo).count() << " ms\n";
    cout << "Skirstymas:   " << duration_cast<milliseconds>(end_skirstymo - start_skirstymo).count() << " ms\n";
}
// Skirstymas naudojant remove_if + erase (pašalina vargšiukus iš originalo)
void testuotiStrategija2Vector(const string& failas) {
    vector<duomenys> visi, vargsiukai;
    ifstream in(failas);
    string eilute;
    getline(in, eilute); // praleidžiama antraštė

    auto start_nuskaitymo = high_resolution_clock::now();
    while (getline(in, eilute)) {
        stringstream ss(eilute);
        duomenys s;
        ss >> s.v >> s.p;
        int paz;
        while (ss >> paz) s.N.push_back(paz);
        s.e = s.N.back(); s.N.pop_back();
        s.paz = s.N.size();
        s.r = 0.4 * accumulate(s.N.begin(), s.N.end(), 0.0) / s.paz + 0.6 * s.e;
        visi.push_back(s);
    }
    auto end_nuskaitymo = high_resolution_clock::now();

    // Pašalinami visi < 5 ir pridedami prie vargšiukų
    auto start_skirstymo = high_resolution_clock::now();
    auto it = remove_if(visi.begin(), visi.end(), [&](const duomenys& s) {
        if (s.r < 5.0) {
            vargsiukai.push_back(s);
            return true; // pažymėti pašalinimui
        }
        return false;
        });
    visi.erase(it, visi.end()); // fizinis pašalinimas
    auto end_skirstymo = high_resolution_clock::now();

    cout << "\n[Vector - Strategija 2] Failas: " << failas << "\n";
    cout << "Nuskaitymas: " << duration_cast<milliseconds>(end_nuskaitymo - start_nuskaitymo).count() << " ms\n";
    cout << "Skirstymas (su ištrynimu): " << duration_cast<milliseconds>(end_skirstymo - start_skirstymo).count() << " ms\n";
}

void testuotiStrategija2List(const string& failas) {
    list<duomenys> visi, vargsiukai;
    ifstream in(failas);
    string eilute;
    getline(in, eilute);

    auto start_nuskaitymo = high_resolution_clock::now();
    while (getline(in, eilute)) {
        stringstream ss(eilute);
        duomenys s;
        ss >> s.v >> s.p;
        int paz;
        while (ss >> paz) s.N.push_back(paz);
        s.e = s.N.back(); s.N.pop_back();
        s.paz = s.N.size();
        s.r = 0.4 * accumulate(s.N.begin(), s.N.end(), 0.0) / s.N.size() + 0.6 * s.e;
        visi.push_back(s);
    }
    auto end_nuskaitymo = high_resolution_clock::now();

    auto start_skirstymo = high_resolution_clock::now();
    for (auto it = visi.begin(); it != visi.end(); ) {
        if (it->r < 5.0) {
            vargsiukai.push_back(*it);
            it = visi.erase(it);
        }
        else {
            ++it;
        }
    }
    auto end_skirstymo = high_resolution_clock::now();

    cout << "\n[List - Strategija 2] Failas: " << failas << "\n";
    cout << "Nuskaitymas: " << duration_cast<milliseconds>(end_nuskaitymo - start_nuskaitymo).count() << " ms\n";
    cout << "Skirstymas (su ištrynimu): " << duration_cast<milliseconds>(end_skirstymo - start_skirstymo).count() << " ms\n";
}
void testuotiStrategija2Deque(const string& failas) {
    deque<duomenys> visi, vargsiukai;
    ifstream in(failas);
    string eilute;
    getline(in, eilute);

    auto start_nuskaitymo = high_resolution_clock::now();
    while (getline(in, eilute)) {
        stringstream ss(eilute);
        duomenys s;
        ss >> s.v >> s.p;
        int paz;
        while (ss >> paz) s.N.push_back(paz);
        s.e = s.N.back(); s.N.pop_back();
        s.paz = s.N.size();
        s.r = 0.4 * accumulate(s.N.begin(), s.N.end(), 0.0) / s.N.size() + 0.6 * s.e;
        visi.push_back(s);
    }
    auto end_nuskaitymo = high_resolution_clock::now();

    auto start_skirstymo = high_resolution_clock::now();
    auto it = remove_if(visi.begin(), visi.end(), [&](const duomenys& s) {
        if (s.r < 5.0) {
            vargsiukai.push_back(s);
            return true;
        }
        return false;
        });
    visi.erase(it, visi.end());
    auto end_skirstymo = high_resolution_clock::now();

    cout << "\n[Deque - Strategija 2] Failas: " << failas << "\n";
    cout << "Nuskaitymas: " << duration_cast<milliseconds>(end_nuskaitymo - start_nuskaitymo).count() << " ms\n";
    cout << "Skirstymas (su ištrynimu): " << duration_cast<milliseconds>(end_skirstymo - start_skirstymo).count() << " ms\n";
}
// Naudoja std::partition – padalina vektorių į dvi grupes pagal sąlygą
void testuotiStrategija3Vector(const string& failas) {
    vector<duomenys> visi;
    ifstream in(failas);
    string eilute;
    getline(in, eilute);

    auto start_nuskaitymo = high_resolution_clock::now();
    while (getline(in, eilute)) {
        stringstream ss(eilute);
        duomenys s;
        ss >> s.v >> s.p;
        int paz;
        while (ss >> paz) s.N.push_back(paz);
        s.e = s.N.back(); s.N.pop_back();
        s.paz = s.N.size();
        s.r = 0.4 * accumulate(s.N.begin(), s.N.end(), 0.0) / s.paz + 0.6 * s.e;
        visi.push_back(s);
    }
    auto end_nuskaitymo = high_resolution_clock::now();

    // Partition: kietiakiai pirmi, vargšiukai – gale
    auto start_partition = high_resolution_clock::now();
    auto it = partition(visi.begin(), visi.end(), [](const duomenys& s) {
        return s.r >= 5.0;
        });
    vector<duomenys> kietiakiai(visi.begin(), it);
    vector<duomenys> vargsiukai(it, visi.end());
    auto end_partition = high_resolution_clock::now();

    cout << "\n[Vector - Strategija 3] Failas: " << failas << "\n";
    cout << "Nuskaitymas: " << duration_cast<milliseconds>(end_nuskaitymo - start_nuskaitymo).count() << " ms\n";
    cout << "Partition skirstymas: " << duration_cast<milliseconds>(end_partition - start_partition).count() << " ms\n";
}

void testuotiStrategija3List(const string& failas) {
    list<duomenys> visi;
    ifstream in(failas);
    string eilute;
    getline(in, eilute);

    auto start_nuskaitymo = high_resolution_clock::now();
    while (getline(in, eilute)) {
        stringstream ss(eilute);
        duomenys s;
        ss >> s.v >> s.p;
        int paz;
        while (ss >> paz) s.N.push_back(paz);
        s.e = s.N.back(); s.N.pop_back();
        s.paz = s.N.size();
        s.r = 0.4 * accumulate(s.N.begin(), s.N.end(), 0.0) / s.N.size() + 0.6 * s.e;
        visi.push_back(s);
    }
    auto end_nuskaitymo = high_resolution_clock::now();

    auto start_skirstymo = high_resolution_clock::now();
    list<duomenys> vargsiukai, kietiakiai;

    for (const auto& s : visi) {
        if (s.r < 5.0) vargsiukai.push_back(s);
        else kietiakiai.push_back(s);
    }
    auto end_skirstymo = high_resolution_clock::now();

    cout << "\n[List - Strategija 3] Failas: " << failas << "\n";
    cout << "Nuskaitymas: " << duration_cast<milliseconds>(end_nuskaitymo - start_nuskaitymo).count() << " ms\n";
    cout << "Efektyvus skirstymas: " << duration_cast<milliseconds>(end_skirstymo - start_skirstymo).count() << " ms\n";
}
void testuotiStrategija3Deque(const string& failas) {
    deque<duomenys> visi;
    ifstream in(failas);
    string eilute;
    getline(in, eilute);

    auto start_nuskaitymo = high_resolution_clock::now();
    while (getline(in, eilute)) {
        stringstream ss(eilute);
        duomenys s;
        ss >> s.v >> s.p;
        int paz;
        while (ss >> paz) s.N.push_back(paz);
        s.e = s.N.back(); s.N.pop_back();
        s.paz = s.N.size();
        s.r = 0.4 * accumulate(s.N.begin(), s.N.end(), 0.0) / s.N.size() + 0.6 * s.e;
        visi.push_back(s);
    }
    auto end_nuskaitymo = high_resolution_clock::now();

    auto start_partition = high_resolution_clock::now();
    auto it = partition(visi.begin(), visi.end(), [](const duomenys& s) {
        return s.r >= 5.0;
        });
    deque<duomenys> kietiakiai(visi.begin(), it);
    deque<duomenys> vargsiukai(it, visi.end());
    auto end_partition = high_resolution_clock::now();

    cout << "\n[Deque - Strategija 3] Failas: " << failas << "\n";
    cout << "Nuskaitymas: " << duration_cast<milliseconds>(end_nuskaitymo - start_nuskaitymo).count() << " ms\n";
    cout << "Partition skirstymas: " << duration_cast<milliseconds>(end_partition - start_partition).count() << " ms\n";
}


