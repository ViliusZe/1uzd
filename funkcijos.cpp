#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <random>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <limits>
#include <chrono>
using namespace std::chrono;

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
void generuotiPasirinktaFaila() {
    int pasirinkimas;
    std::cout << "Pasirinkite, kiek įrašų turės sugeneruotas failas:\n";
    std::cout << "1 - 1 000 studentų\n";
    std::cout << "2 - 10 000 studentų\n";
    std::cout << "3 - 100 000 studentų\n";
    std::cout << "4 - 1 000 000 studentų\n";
    std::cout << "5 - 10 000 000 studentų\n";
    std::cin >> pasirinkimas;

    if (std::cin.fail()) {
        std::cerr << "Klaida: įvestas ne skaičius.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return;
    }

    switch (pasirinkimas) {
        case 1:
            generuotiFaila("studentai_1k.txt", 1000);
            break;
        case 2:
            generuotiFaila("studentai_10k.txt", 10000);
            break;
        case 3:
            generuotiFaila("studentai_100k.txt", 100000);
            break;
        case 4:
            generuotiFaila("studentai_1mln.txt", 1000000);
            break;
        case 5:
            generuotiFaila("studentai_10mln.txt", 10000000);
            break;
        default:
            std::cout << "Neteisingas pasirinkimas.\n";
    }
}
void analizuotiPasirinktaFaila() {
    int pasirinkimas;
    std::string failas;

    std::cout << "Pasirinkite, kurį failą analizuoti:\n";
    std::cout << "1 - studentai_1k.txt\n";
    std::cout << "2 - studentai_10k.txt\n";
    std::cout << "3 - studentai_100k.txt\n";
    std::cout << "4 - studentai_1mln.txt\n";
    std::cout << "5 - studentai_10mln.txt\n";
    std::cin >> pasirinkimas;

    if (std::cin.fail()) {
        std::cerr << "Klaida: įvestas ne skaičius.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return;
    }

    switch (pasirinkimas) {
        case 1: failas = "studentai_1k.txt"; break;
        case 2: failas = "studentai_10k.txt"; break;
        case 3: failas = "studentai_100k.txt"; break;
        case 4: failas = "studentai_1mln.txt"; break;
        case 5: failas = "studentai_10mln.txt"; break;
        default:
            std::cout << "Neteisingas pasirinkimas.\n";
            return;
    }

    analizuotiFaila(failas);
}


long long analizuotiFaila(const std::string& failoVardas) {
    auto pradzia = std::chrono::high_resolution_clock::now();

    std::ifstream in(failoVardas);
    if (!in) {
        std::cerr << "Nepavyko atidaryti failo: " << failoVardas << std::endl;
        return -1;
    }

    std::string eilute;
    getline(in, eilute); // antraštė

    std::vector<duomenys> kietiakiai;
    std::vector<duomenys> vargsiukai;

    auto nuskaitymas_start = std::chrono::high_resolution_clock::now();

    while (getline(in, eilute)) {
        std::stringstream ss(eilute);
        duomenys s;
        ss >> s.v >> s.p;

        int pazymys;
        while (ss >> pazymys) {
            s.N.push_back(pazymys);
        }

        if (s.N.empty()) continue;

        s.e = s.N.back();
        s.N.pop_back();
        s.paz = s.N.size();

        double vid = 0.0;
        for (int n : s.N) vid += n;
        vid = s.N.empty() ? 0 : vid / s.N.size();
        s.r = 0.4 * vid + 0.6 * s.e;

        if (s.r < 5.0)
            vargsiukai.push_back(s);
        else
            kietiakiai.push_back(s);
    }
    in.close();

    auto nuskaitymas_end = std::chrono::high_resolution_clock::now();

    auto isvedimas_start = std::chrono::high_resolution_clock::now();

    std::ofstream out1("vargsiukai.txt");
    std::ofstream out2("kietiakiai.txt");

    for (const auto& s : vargsiukai)
        out1 << s.p << " " << s.v << " " << s.r << "\n";
    for (const auto& s : kietiakiai)
        out2 << s.p << " " << s.v << " " << s.r << "\n";

    out1.close();
    out2.close();

    auto isvedimas_end = std::chrono::high_resolution_clock::now();
    auto pabaiga = std::chrono::high_resolution_clock::now();

    // Laiko skaičiavimai (milisekundėmis)
    auto t_nuskaitymas = std::chrono::duration_cast<std::chrono::milliseconds>(nuskaitymas_end - nuskaitymas_start).count();
    auto t_isvedimas   = std::chrono::duration_cast<std::chrono::milliseconds>(isvedimas_end - isvedimas_start).count();
    auto t_visas       = std::chrono::duration_cast<std::chrono::milliseconds>(pabaiga - pradzia).count();

    std::cout << "Analizė baigta: " << vargsiukai.size() << " vargšiukai, " << kietiakiai.size() << " kietiakiai.\n";
    std::cout << "---- Laiko analizė ----\n";
    std::cout << "Failo nuskaitymas + skirstymas: " << t_nuskaitymas << " ms\n";
    std::cout << "Išvedimas į failus: " << t_isvedimas << " ms\n";
    std::cout << "Bendras analizės laikas: " << t_visas / 1000.0 << " s\n";
    std::cout << "------------------------\n";

    return t_visas;
}

void atliktiAnalize() {
    int tyrimas;
    std::cout << "Pasirinkite tyrimo tipą:\n";
    std::cout << "1 - Failo kūrimo greitis (be analizės)\n";
    std::cout << "2 - Pilna analizė: nuskaitymas, rūšiavimas, išvedimas\n";
    std::cin >> tyrimas;

    if (std::cin.fail() || (tyrimas != 1 && tyrimas != 2)) {
        std::cerr << "Klaida: įveskite 1 arba 2.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return;
    }

    std::vector<std::pair<std::string, int>> failai = {
        {"studentai_1k.txt", 1000},
        {"studentai_10k.txt", 10000},
        {"studentai_100k.txt", 100000},
        {"studentai_1mln.txt", 1000000},
        {"studentai_10mln.txt", 10000000}
    };

    for (const auto& [failas, kiekis] : failai) {
        std::cout << "\nFailas: " << failas << "\n";

        if (tyrimas == 1) {
            auto start = std::chrono::high_resolution_clock::now();
            generuotiFaila(failas, kiekis);
            auto end = std::chrono::high_resolution_clock::now();
            
            auto laikasMs = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
            std::cout << "Sukūrimo laikas: " << laikasMs << " ms (" << laikasMs / 1000.0 << " s)\n";

        } else if (tyrimas == 2) {
            long long trukme = analizuotiFaila(failas);
            if (trukme >= 0)
            std::cout << "Apdorota per: " << trukme / 1000.0 << " s\n";
        }
        }
    std::cout << "\nTyrimas baigtas.\n";
}


