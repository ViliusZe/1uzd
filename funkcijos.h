#ifndef FUNKCIJOS_H
#define FUNKCIJOS_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct duomenys {
    string v, p;
    vector<int> N;
    int paz;
    int e;
    double r;
};

bool tikrintiVardaPavarde(const string &tekstas);
double vid(const vector<int>& N);
double mediana(vector<int>& N);
int gautiPasirinkima();
bool noriTęsti();
void skaitymas(vector<duomenys>& M);
void skaiciavimas(vector<duomenys>& M, int pasirinkimas);
void rikiuotiMokinius(vector<duomenys>& M, int pasirinkimas, bool atvirkstine);
void rasymas(const vector<duomenys>& M);
void generuotiVardusPavardesIrPazymius(vector<duomenys>& M);
void generuotiPazymius(vector<duomenys>& M);
void skaitymasIsFailo(vector<duomenys>& M, const string& failoPavadinimas);
void rasymasIFaila(const vector<duomenys>& M);
void generuotiFaila(const std::string& failoVardas, int kiekis);
void generuotiPasirinktaFaila();
void analizuotiFaila(const std::string& failoVardas);
void analizuotiPasirinktaFaila();


#endif
