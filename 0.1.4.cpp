#include <iostream>
#include <iomanip>
#include <vector>
#include <random>
#include <algorithm>
using namespace std;

struct duomenys {
    string v, p;  // Vardas ir pavardė
    vector<int> N;  // Pažymiai
    int paz;  // Pažymių skaičius
    int e;  // Egzamino rezultatas
    double r;  // Galutinis rezultatas
};
bool tikrintiVardaPavarde(const string &tekstas) 
{
    for (char c : tekstas) 
    {
        if (!isalpha(c)) return false;  
    }
    return true;
}
double vid(const vector<int>& N) { 
    double sum = 0;
    for (int i = 0; i < N.size(); i++) 
    {
        sum += N[i];  
    }
    return N.size() > 0 ? sum / N.size() : 0;  
}
double mediana(vector<int>& N) 
{  
    sort(N.begin(), N.end());  
    if (N.size() % 2 != 0) 
    {
        return N[N.size() / 2];  
    }
    else 
    {
        return (N[(N.size() - 1) / 2] + N[N.size() / 2]) / 2.0;
    }
}
int gautiPasirinkima() 
{
    int pasirinkimas;
    while (true) 
    {
        cout << "Jei norima skaiciuoti mokinio vidurkį, įveskite 1, jei medianą - 0:" << endl;
        cin >> pasirinkimas;
        if (cin.fail() || (pasirinkimas != 0 && pasirinkimas != 1)) 
        {
            cout << "Neteisingas pasirinkimas. Prašome įvesti 1 arba 0." << endl;
            cin.clear();  
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  
        } 
        else 
        {
            return pasirinkimas;
        }
    }
}
bool noriTęsti() 
{
    string testi;
    while (true) 
    {
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
void skaitymas(vector<duomenys>& M) 
{
    do {
        duomenys temp;
        do {
            cout << "Įveskite mokinio vardą: ";
            cin >> temp.v;
            if (!tikrintiVardaPavarde(temp.v)) 
            {
                cout << "Neteisingas vardas. Bandykite dar kartą.\n";
            }
        } 
        while (!tikrintiVardaPavarde(temp.v));
        do {
            cout << "Įveskite mokinio pavardę: ";
            cin >> temp.p;
            if (!tikrintiVardaPavarde(temp.p)) 
            {
                cout << "Neteisinga pavardė. Bandykite dar kartą.\n";
            }
        } 
        while (!tikrintiVardaPavarde(temp.p));
        cout << "Įveskite mokinio pažymius (baigti įveskite -1): ";
        temp.paz = 0;
        int pazymys;
        while (true) 
        {
            cin >> pazymys;
            if (pazymys == -1) break;  
            if (pazymys < 1 || pazymys > 10) 
            {
                cout << "Pažymys turi būti tarp 1 ir 10. Bandykite dar kartą: ";
                continue;
            }
            temp.N.push_back(pazymys);  
            temp.paz++;
        }
        do {
            cout << "Įveskite mokinio egzamino rezultatą (1-10): ";
            cin >> temp.e;
            if (cin.fail() || temp.e < 1 || temp.e > 10) 
            {
                cout << "Egzamino rezultatas turi būti tarp 1 ir 10. Bandykite dar kartą.\n";
                cin.clear();  
                cin.ignore(numeric_limits<streamsize>::max(), '\n');  
            }
        } 
        while (temp.e < 1 || temp.e > 10);
        M.push_back(temp);  
    } 
    while (noriTęsti());  
}
void skaiciavimas(vector<duomenys>& M, int pasirinkimas) 
{
    for (int i = 0; i < M.size(); i++) 
    {
        if (pasirinkimas == 1) 
        {
            M[i].r = vid(M[i].N) * 0.4 + M[i].e * 0.6;  
        } 
        else 
        {
            M[i].r = mediana(M[i].N) * 0.4 + M[i].e * 0.6;  
        }
    }
}
void rasymas(const vector<duomenys>& M) 
{
    cout << left << setw(18) << setfill(' ') << "Pavardė" << left << setw(18) << "Vardas" << "Galutinis" << endl;
    cout << setw(50) << setfill('-') << "-" << endl;
    for (int i = 0; i < M.size(); i++) 
    {
        cout << left << setw(17) << setfill(' ') << M[i].p << left << setw(18) << M[i].v << fixed << setprecision(2) << M[i].r << endl;
    }
}


void generuotiVardusPavardesIrPazymius(vector<duomenys>& M) 
{
    
    vector<string> vyriskiVardai = {"Jonas", "Petras", "Marius", "Tomas", "Andrius"};
    vector<string> moteriskiVardai = {"Ona", "Eglė", "Ieva", "Rūta", "Laura"};
    
    vector<string> vyriskiPavardes = {"Kazlauskas", "Jankauskas", "Petravičius", "Navickas", "Butkus"};
    vector<string> moteriskiPavardes = {"Butkienė", "Vaitkevičienė", "Jankauskaitė", "Kazlauskaitė", "Petravičienė"};
    
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> vardas_distrib(0, 4);  
    uniform_int_distribution<> pavarde_distrib(0, 4);  
    uniform_int_distribution<> pazymys_distrib(1, 10);  
    uniform_int_distribution<> lytis_distrib(0, 1);  
    
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
        } else 
        {
            break;
        }
    }
    for (int i = 0; i < mokiniuKiekis; i++) 
    {
        duomenys temp;
        int lytis = lytis_distrib(gen);  
        if (lytis == 0) 
        {  
            temp.v = vyriskiVardai[vardas_distrib(gen)];
            temp.p = vyriskiPavardes[pavarde_distrib(gen)];
        } else 
        {  
            temp.v = moteriskiVardai[vardas_distrib(gen)];
            temp.p = moteriskiPavardes[pavarde_distrib(gen)];
        }
        temp.paz = rand() % 5 + 5;  
        for (int j = 0; j < temp.paz; j++) 
        {
            temp.N.push_back(pazymys_distrib(gen));  
        }
        temp.e = pazymys_distrib(gen);  
        M.push_back(temp);  
    }
}
void generuotiPazymius(vector<duomenys>& M) 
{
    string pasirinkimas;
    do 
    {
        duomenys temp;
        cout << "Įveskite mokinio vardą: ";
        cin >> temp.v;
        cout << "Įveskite mokinio pavardę: ";
        cin >> temp.p;
        cout << "Įveskite pažymių kiekį: ";
        cin >> temp.paz;  
        random_device rd;  
        mt19937 gen(rd());  
        uniform_int_distribution<> distrib(1, 10);
        for (int j = 0; j < temp.paz; j++) 
        {
            temp.N.push_back(distrib(gen));  
        }
        temp.e = distrib(gen);
        M.push_back(temp);  
        cout << "Ar norite pridėti dar vieną mokinį? (Taip/Ne): ";
        cin >> pasirinkimas;
    } 
    while (pasirinkimas == "Taip" || pasirinkimas == "taip");  
}
int main() 
{
    vector<duomenys> M;  
    int pasirinkimas;
    int vidMed;  
    while (true) 
    {
        cout << "Pasirinkite programa:\n";
        cout << "1 - Ranką\n";
        cout << "2 - Generuoti tik pažymius\n";
        cout << "3 - Generuoti studentų vardus, pavardes ir pažymius\n";
        cout << "4 - Baigti darbą\n";
        cout << "Pasirinkimas: ";
        cin >> pasirinkimas;
        switch (pasirinkimas) 
        {
            case 1:
                skaitymas(M);
                vidMed = gautiPasirinkima();  
                skaiciavimas(M, vidMed);
                rasymas(M);
                M.clear();  
                break;
            case 2:
                // Generuoti tik pažymius
                cout << "Generuojami tik pazymiai...\n";
                generuotiPazymius(M);  
                vidMed = gautiPasirinkima();  
                skaiciavimas(M, vidMed);
                rasymas(M);
                M.clear();  
                break;
            case 3:
                
                cout << "Generuojami studentų vardai, pavardės ir pažymiai...\n";
                generuotiVardusPavardesIrPazymius(M);  
                vidMed = gautiPasirinkima();  
                skaiciavimas(M, vidMed);
                rasymas(M);
                M.clear();  
                break;
            case 4:
                cout << "Programa baigta.\n";
                return 0;  
            default:
                cout << "Neteisingas pasirinkimas. Bandykite dar kartą.\n";
        }
    }
    return 0;  
}