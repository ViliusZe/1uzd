#include <iostream>  
#include <iomanip>
#include <vector>    // Įtraukiama vektoriaus (dynamic array) biblioteka, naudojama saugoti mokinių duomenis.
#include <random>    // Įtraukiama atsitiktinių skaičių generavimo biblioteka, naudojama sugeneruoti atsitiktinius pažymius.
#include <algorithm> // Įtraukiama algoritmų biblioteka, reikalinga tokioms operacijoms kaip `sort()` (rūšiavimas).
#include <sstream>    // Reikalinga stringstream klasei
#include <fstream>    // Reikalinga ifstream klasei

using namespace std;  
// Struktūra mokinio duomenims saugoti.
struct duomenys 
{  
    string v, p;  // Vardas ir pavardė.
    vector<int> N;  // Pažymiai (dinaminis).
    int paz;  // Pažymių skaičius.
    int e;  // Egzamino rezultatas.
    double r;  // Galutinis rezultatas (apskaičiuotas remiantis pažymiais ir egzaminu).
};

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
void skaitymas(vector<duomenys>& M) 
{
    do 
    {
        duomenys temp;  // Laikinas studento duomenų objektas.
        do 
        {
            cout << "Įveskite mokinio vardą: ";
            cin >> temp.v;
            if (!tikrintiVardaPavarde(temp.v)) // Tikrinama, ar vardas yra teisingas.
            {  
                cout << "Neteisingas vardas. Bandykite dar kartą.\n";
            }
        } 
        while (!tikrintiVardaPavarde(temp.v));  // Pakartojama, kol įvestas teisingas vardas.
        do 
        {
            cout << "Įveskite mokinio pavardę: ";
            cin >> temp.p;
            if (!tikrintiVardaPavarde(temp.p)) // Tikrinama, ar pavardė yra teisinga.
            {  
                cout << "Neteisinga pavardė. Bandykite dar kartą.\n";
            }
        } 
        while (!tikrintiVardaPavarde(temp.p));  // Pakartojama, kol įvestas teisingas pavardė.
        cout << "Įveskite mokinio pažymius (baigti įveskite -1): ";
        temp.paz = 0;
        int pazymys;
        while (true) 
        {
            cin >> pazymys;
            if (pazymys == -1) break;  // Baigti įvedimą, jei įvestas -1.
            if (pazymys < 1 || pazymys > 10) // Tikrinama, ar pažymiai yra tarp 1 ir 10.
            {  
                cout << "Pažymys turi būti tarp 1 ir 10. Bandykite dar kartą: ";
                continue;
            }
            temp.N.push_back(pazymys);  // Pridedama pažymį į studento vektorių.
            temp.paz++;  // Didinamas pažymių skaičius.
        }
        do 
        {
            cout << "Įveskite mokinio egzamino rezultatą (1-10): ";
            cin >> temp.e;
            if (cin.fail() || temp.e < 1 || temp.e > 10) 
            {  // Tikrinama, ar egzaminų rezultatas yra teisingas.
                cout << "Egzamino rezultatas turi būti tarp 1 ir 10. Bandykite dar kartą.\n";
                cin.clear();  // Valoma klaidos būsena.
                cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Ignoruojami papildomi simboliai.
            }
        } 
        while (temp.e < 1 || temp.e > 10);  // Pakartojama, kol įvestas teisingas egzaminų rezultatas.
        M.push_back(temp);  // Įrašomas studento duomenys į vektorių.
    } 
    while (noriTęsti());  // Klausimas, ar norima įvesti dar vieną mokinį.
}

// Funkcija apskaičiuoti galutinius rezultatus remiantis pasirinktu metodiku.
void skaiciavimas(vector<duomenys>& M, int pasirinkimas) 
{
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
        cout << "Nepavyko atidaryti failo!" << endl;
        return;
    }
    string eilute;
    getline(failas, eilute);  // Praleidžiame pirmą eilutę (antraštę)

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

// Pagrindinė funkcija.
int main() 
{
    string failoPavadinimas = "studentai10000.txt";
    vector<duomenys> M;  // Vektorius, saugosiantis visų mokinių duomenis.
    int pasirinkimas;
    do {
        cout << "Pasirinkite viena is ju:" << endl;
        cout << "1. Įvesti mokinių duomenis" << endl;
        cout << "2. Sugeneruoti tik pažymius" << endl;
        cout << "3. Sugeneruoti visus duomenis" << endl;
        cout << "4. Skaityti duomenis iš failo" << endl;
        cout << "5. Baigti" << endl;
        cin >> pasirinkimas;  // Gauti vartotojo pasirinkimą.
        switch (pasirinkimas) 
        {
            case 1:
                skaitymas(M);  // Skaito duomenis iš vartotojo.
                skaiciavimas(M, gautiPasirinkima());  // Apskaičiuoja galutinį rezultatą.
                rasymas(M);  // Spausdina rezultatus.
                break;
            case 2:
                generuotiPazymius(M);  // Sugeneruoja tik pažymius.
                break;
            case 3:
                generuotiVardusPavardesIrPazymius(M);  // Sugeneruoja visus duomenis.
                skaiciavimas(M, gautiPasirinkima());  // Apskaičiuoja galutinius rezultatus.
                rasymas(M);  // Spausdina rezultatus.
                break;
            case 4:
                skaitymasIsFailo(M, failoPavadinimas);  // Nauja funkcija skaitanti duomenis iš failo.
                break;
            case 5:
                cout << "Programos pabaiga." << endl;
                break;
            default:
                cout << "Neteisingas pasirinkimas. Bandykite dar kartą." << endl;
                break;
        }
    } while (pasirinkimas != 5);  // Programos pabaiga, kol vartotojas nesirenka 5.
}
