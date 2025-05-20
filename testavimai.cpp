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

void testuotiVector(const string& failas) {

    vector<duomenys> visi, vargsiukai, kietiakiai;
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

    cout << "\n[Vector] Failas: " << failas << "\n";
    cout << "Nuskaitymas: " << duration_cast<milliseconds>(end_nuskaitymo - start_nuskaitymo).count() << " ms\n";
    cout << "Rusiavimas:   " << duration_cast<milliseconds>(end_rusiavimo - start_rusiavimo).count() << " ms\n";
    cout << "Skirstymas:   " << duration_cast<milliseconds>(end_skirstymo - start_skirstymo).count() << " ms\n";
}

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
