#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <random>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <limits>

#include "funkcijos.h"

// Funkcija tikrina, ar pateiktas tekstas yra tinkamas vardas/pavardė (turi būti tik raidės).
bool tikrintiVardaPavarde(const string &tekstas) 
{
    for (char c : tekstas) 
    {
        if (!isalpha(c)) return false;  // Jei randama ne raidė, grąžinama klaida.
    }
    return true;  // Jei visi simboliai yra raidės, grąžinama tiesa.
}

// Funkcija apskaičiuoti vidurkį pagal pateiktus pažymius.
double vid(const vector<int>& N) 
{ 
    double sum = 0;
    for (int i = 0; i < N.size(); i++) 
    {
        sum += N[i];  // Skaičiuojamas pažymių suma.
    }
    return N.size() > 0 ? sum / N.size() : 0;  // Jei yra pažymių, grąžinamas vidurkis, kitaip 0.
}

// Funkcija apskaičiuoti medianą pagal pateiktus pažymius.
double mediana(vector<int>& N) 
{  
    sort(N.begin(), N.end());  // Rūšiuojami pažymiai.
    if (N.size() % 2 != 0) 
    {  // Jei neporinis elementų skaičius, grąžinama vidurinė reikšmė.
        return N[N.size() / 2];  
    } 
    else 
    {  // Jei porinis, grąžinama dviejų vidurinių reikšmių vidurkis.
        return (N[(N.size() - 1) / 2] + N[N.size() / 2]) / 2.0;
    }
}
// Funkcija klausia vartotojo, kokį apskaičiavimą atlikti: vidurkį ar medianą.
int gautiPasirinkima() 
{
    int pasirinkimas;
    while (true) 
    {
        cout << "Jei norima skaiciuoti mokinio vidurkį, įveskite 1, jei medianą - 0:" << endl;
        cin >> pasirinkimas;
        if (cin.fail() || (pasirinkimas != 0 && pasirinkimas != 1)) {  // Tikrinama, ar pasirinkimas yra 0 arba 1.
            cout << "Neteisingas pasirinkimas. Prašome įvesti 1 arba 0." << endl;
            cin.clear();  // Valoma klaidos būsena.
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Ignoruojami visi papildomi simboliai.
        } 
        else 
        {
            return pasirinkimas;
        }
    }
}

// Funkcija klausia vartotojo, ar nori tęsti įrašą.
bool noriTęsti() 
{
    string testi;
    while (true) {
        cout << "Ar norite įvesti dar vieną mokinį? (Taip/Ne): ";
        cin >> testi;
        if (testi == "Taip" || testi == "taip") 
        {
            return true;
        } 
        else if (testi == "Ne" || testi == "ne") 
        {
            return false;
        } 
        else 
        {
            cout << "Neteisingas atsakymas. Prašome įvesti 'Taip' arba 'Ne'." << endl;
        }
    }
}

// Funkcija skaityti ir įvesti mokinių duomenis.
void skaitymas(vector<duomenys>& M) {
    do {
        duomenys temp;

        // Vardo įvedimas su tikrinimu
        do {
            cout << "Įveskite mokinio vardą: ";
            try {
                cin >> temp.v;
                if (!tikrintiVardaPavarde(temp.v)) throw std::invalid_argument("Varde turi būti tik raidės.");
            } catch (const std::exception& e) {
                cout << "Klaida: " << e.what() << " Bandykite dar kartą.\n";
                continue;
            }
            break;
        } while (true);

        // Pavardės įvedimas su tikrinimu
        do {
            cout << "Įveskite mokinio pavardę: ";
            try {
                cin >> temp.p;
                if (!tikrintiVardaPavarde(temp.p)) throw std::invalid_argument("Pavardėje turi būti tik raidės.");
            } catch (const std::exception& e) {
                cout << "Klaida: " << e.what() << " Bandykite dar kartą.\n";
                continue;
            }
            break;
        } while (true);

        // Pažymių įvedimas
        cout << "Įveskite mokinio pažymius (baigti įveskite -1): ";
        temp.paz = 0;
        int pazymys;
        while (true) {
            try {
                cin >> pazymys;
                if (cin.fail()) throw std::runtime_error("Turite įvesti sveikąjį skaičių.");
                if (pazymys == -1) break;
                if (pazymys < 1 || pazymys > 10) throw std::out_of_range("Pažymys turi būti tarp 1 ir 10.");
                temp.N.push_back(pazymys);
                temp.paz++;
            } catch (const std::exception& e) {
                cout << "Klaida: " << e.what() << " Bandykite dar kartą: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }

        // Egzamino rezultato įvedimas
        do {
            cout << "Įveskite mokinio egzamino rezultatą (1-10): ";
            try {
                cin >> temp.e;
                if (cin.fail()) throw std::runtime_error("Turite įvesti sveikąjį skaičių.");
                if (temp.e < 1 || temp.e > 10) throw std::out_of_range("Egzamino rezultatas turi būti nuo 1 iki 10.");
            } catch (const std::exception& e) {
                cout << "Klaida: " << e.what() << " Bandykite dar kartą.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            break;
        } while (true);

        M.push_back(temp);

    } while (noriTęsti());
}


// Funkcija apskaičiuoti galutinius rezultatus remiantis pasirinktu metodiku.
void rikiuotiMokinius(vector<duomenys>& M, int pasirinkimas, bool atvirkstine)
{
    if (pasirinkimas == 0) // Rūšiavimas pagal pavardę
    {  
        if (atvirkstine) 
        {
            sort(M.begin(), M.end(), [](const duomenys& a, const duomenys& b) 
            {
                return a.p > b.p;  // Atvirkštine tvarka
            });
        }
        else {
            sort(M.begin(), M.end(), [](const duomenys& a, const duomenys& b) 
            {
                return a.p < b.p;  // Didėjančia tvarka
            });
        }
    }
    else if (pasirinkimas == 1) 
    {  // Rūšiavimas pagal vardą
        if (atvirkstine) 
        {
            sort(M.begin(), M.end(), [](const duomenys& a, const duomenys& b) 
            {
                return a.v > b.v;
            });
        }
        else 
        {
            sort(M.begin(), M.end(), [](const duomenys& a, const duomenys& b) 
            {
                return a.v < b.v;
            });
        }
    }
    else if (pasirinkimas == 2) // Rūšiavimas pagal galutinį rezultatą (vidurkį)
    {  
        if (atvirkstine) 
        {
            sort(M.begin(), M.end(), [](const duomenys& a, const duomenys& b) 
            {
                return a.r > b.r;
            });
        }
        else 
        {
            sort(M.begin(), M.end(), [](const duomenys& a, const duomenys& b) 
            {
                return a.r < b.r;
            });
        }
    }
}


// Pridėti rusiavimą po galutinio rezultato apskaičiavimo
void skaiciavimas(vector<duomenys>& M, int pasirinkimas)
{
    bool atvirkstine;
    for (int i = 0; i < M.size(); i++) 
    {
        if (pasirinkimas == 1) 
        {  // Jei pasirinktas vidurkis:
            M[i].r = vid(M[i].N) * 0.4 + M[i].e * 0.6;
        } 
        else 
        {  // Jei pasirinkta mediana:
            M[i].r = mediana(M[i].N) * 0.4 + M[i].e * 0.6;
        }
    }

    // Pasirinkti rūšiavimą pagal vartotojo pasirinkimą
    int rusiavimoPasirinkimas;
    cout << "Pagal ką norite rūšiuoti?\n";
    cout << "0. Pavardė\n";
    cout << "1. Vardas\n";
    cout << "2. Galutinis pagal vidurkį arba mediana\n";
    cin >> rusiavimoPasirinkimas;
    cout << "Kaip norite rūšiuoti?\n";
    cout << "0. Didėjančiai\n";
    cout << "1. Mažėjančiai\n";
    cin>> atvirkstine;
    
    rikiuotiMokinius(M, rusiavimoPasirinkimas, atvirkstine);  // Rūšiuojame pagal vartotojo pasirinkimą
}

// Funkcija spausdina mokinių duomenis su galutiniais rezultatais.
void rasymas(const vector<duomenys>& M) 
{
    cout << left << setw(18) << setfill(' ') << "Pavardė" << left << setw(18) << "Vardas" << "Galutinis" << endl;
    cout << setw(50) << setfill('-') << "-" << endl;
    for (int i = 0; i < M.size(); i++) 
    {
        cout << left << setw(17) << setfill(' ') << M[i].p << left << setw(18) << M[i].v << fixed << setprecision(2) << M[i].r << endl;
    }
}

// Funkcija generuoti atsitiktinius mokinių duomenis.
void generuotiVardusPavardesIrPazymius(vector<duomenys>& M) 
{
    // Vardų, pavardžių ir lyties pasirinkimai.
    vector<string> vyriskiVardai = {"Jonas", "Petras", "Marius", "Tomas", "Andrius"};
    vector<string> moteriskiVardai = {"Ona", "Eglė", "Ieva", "Rūta", "Laura"};
    vector<string> vyriskiPavardes = {"Kazlauskas", "Jankauskas", "Petravičius", "Navickas", "Butkus"};
    vector<string> moteriskiPavardes = {"Butkienė", "Vaitkevičienė", "Jankauskaitė", "Kazlauskaitė", "Petravičienė"};

    random_device rd;  // Atsitiktinių skaičių generatorius.
    mt19937 gen(rd());  // Generatorius naudojantis šį atsitiktinį šaltinį.
    uniform_int_distribution<> vardas_distrib(0, 4);  // Atsitiktinis pasirinkimas iš vardų sąrašo.
    uniform_int_distribution<> pavarde_distrib(0, 4);  // Atsitiktinis pasirinkimas iš pavardžių sąrašo.
    uniform_int_distribution<> pazymys_distrib(1, 10);  // Atsitiktiniai pažymiai nuo 1 iki 10.
    uniform_int_distribution<> lytis_distrib(0, 1);  // Atsitiktinė lyties parinktis (0 - vyras, 1 - moteris).

    int mokiniuKiekis;
    cout << "Kiek mokinių norite sugeneruoti? ";
    while (true) 
    {
        cin >> mokiniuKiekis;
        if (cin.fail() || mokiniuKiekis <= 0) 
        {
            cout << "Neteisingas įvestas skaičius. Prašome įvesti teigiamą skaičių." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } 
        else 
        {
            break;
        }
    }

    // Generuojame nurodytą kiekį mokinių su atsitiktiniais duomenimis.
    for (int i = 0; i < mokiniuKiekis; i++) 
    {
        duomenys temp;
        int lytis = lytis_distrib(gen);  // Atsitiktinai nustatome lytį.
        if (lytis == 0) 
        {  // Jei vyras, pasirenkame vyrų vardą ir pavardę.
            temp.v = vyriskiVardai[vardas_distrib(gen)];
            temp.p = vyriskiPavardes[pavarde_distrib(gen)];
        } 
        else 
        {  // Jei moteris, pasirenkame moterų vardą ir pavardę.
            temp.v = moteriskiVardai[vardas_distrib(gen)];
            temp.p = moteriskiPavardes[pavarde_distrib(gen)];
        }
        temp.paz = rand() % 5 + 5;  // Atsitiktinis pažymių kiekis nuo 5 iki 9.
        for (int j = 0; j < temp.paz; j++) 
        {
            temp.N.push_back(pazymys_distrib(gen));  // Generuojami pažymiai.
        }
        temp.e = pazymys_distrib(gen);  // Atsitiktinis egzamino rezultatas.
        M.push_back(temp);  // Įtraukiami sugeneruoti duomenys į sąrašą.
    }
}

// Funkcija generuoti tik pažymius.
void generuotiPazymius(vector<duomenys>& M) 
{
    string pasirinkimas;
    do {
        duomenys temp;
        cout << "Įveskite mokinio vardą: ";
        cin >> temp.v;
        cout << "Įveskite mokinio pavardę: ";
        cin >> temp.p;
        cout << "Įveskite pažymių kiekį: ";
        cin >> temp.paz;  // Įvedamas pažymių kiekis.
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> distrib(1, 10);  // Atsitiktiniai pažymiai.
        for (int j = 0; j < temp.paz; j++) 
        {
            temp.N.push_back(distrib(gen));  // Generuojami pažymiai.
        }
        temp.e = distrib(gen);  // Generuojamas egzamino rezultatas.
        M.push_back(temp);  // Įtraukiami duomenys į sąrašą.
    } while (noriTęsti());  // Klausimas, ar tęsti duomenų įvedimą.
}
void skaitymasIsFailo(vector<duomenys>& M, const string& failoPavadinimas) {
    ifstream failas(failoPavadinimas);
    if (!failas) {
        throw std::runtime_error("Nepavyko atidaryti failo: " + failoPavadinimas);
    }

    string eilute;
    getline(failas, eilute); // praleidžiama antraštė

    while (getline(failas, eilute)) {
        stringstream ss(eilute);
        duomenys temp;
        ss >> temp.v >> temp.p;
        int pazymys;
        while (ss >> pazymys) {
            if (ss.peek() == ' ' || ss.peek() == '\t') {
                ss.ignore();
            }
            temp.N.push_back(pazymys);
        }
        if (!temp.N.empty()) {
            temp.e = temp.N.back();
            temp.N.pop_back();
            temp.paz = temp.N.size();
            M.push_back(temp);
        }
    }
    failas.close();
}

// Funkcija rašyti duomenis į failą
void rasymasIFaila(const vector<duomenys>& M) 
{
    ofstream failas("rezultatai.txt");  // Atidaryti failą rašymui, sukurti jei jo nėra

    if (!failas) {
        cout << "Nepavyko atidaryti failo rašymui!" << endl;
        return;
    }

    failas << left << setw(18) << setfill(' ') << "Pavardė" << left << setw(18) << "Vardas" << "Galutinis" << endl;
    failas << setw(50) << setfill('-') << "-" << endl;

    for (int i = 0; i < M.size(); i++) {
        failas << left << setw(17) << setfill(' ') << M[i].p << left << setw(18) << M[i].v << fixed << setprecision(2) << M[i].r << endl;
    }

    failas.close();
    cout << "Duomenys išrašyti į failą: " << "rezultatai.txt" << endl;
}
// Funkcija klausia vartotojo, ar norima rūšiuoti rezultatus
#include <random>
#include <fstream>

void generuotiFaila(const std::string& failoVardas, int kiekis) {
    std::ofstream out(failoVardas);
    if (!out) {
        std::cerr << "Nepavyko sukurti failo: " << failoVardas << std::endl;
        return;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> pazymiuKiekis(5, 15);
    std::uniform_int_distribution<> pazymys(1, 10);

    // Antraštė
    out << "Vardas Pavarde ";
    for (int i = 1; i <= 15; ++i) {
        out << "ND" << i << " ";
    }
    out << "Egzaminas\n";

    for (int i = 1; i <= kiekis; ++i) {
        out << "VardasNR" << i << " PavardeNR" << i << " ";

        int kiek = pazymiuKiekis(gen);
        for (int j = 0; j < kiek; ++j) {
            out << pazymys(gen) << " ";
        }

        out << pazymys(gen) << "\n"; // Egzaminas
    }

    out.close();
    std::cout << "Sugeneruotas failas: " << failoVardas << " (" << kiekis << " įrašų)\n";
}

void generuotiVisusFailus() {
    generuotiFaila("studentai_1k.txt",      1000);
    generuotiFaila("studentai_10k.txt",     10000);
    generuotiFaila("studentai_100k.txt",    100000);
    generuotiFaila("studentai_1mln.txt",    1000000);
    generuotiFaila("studentai_10mln.txt",   10000000);
}
