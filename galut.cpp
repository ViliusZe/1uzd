#include <iomanip>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
using namespace std;
struct duomenys 
{
    string v, p;
    int paz;
    int N[5];
    int e;
    double r;
};
void skaitymas (duomenys M[], int n);
void skaiciavimas (duomenys M[], int n, int m);
double vid (duomenys M[], int i);
double mediana(duomenys M[], int i);
void rezultatai (duomenys M[], int n, int m);
int main()
{
    duomenys M[10];
    int n, m;
    cout<< "Iveskite mokiniu kieki:";
    cin>>n;
    cout<< endl << "Jei norima skaiciuoti mokinio vidurki iveskite 1 jei norima skaiciuoti mediana iveskite 0:";
    cin>>m;
    cout<< endl;
    skaitymas(M, n);
    skaiciavimas (M, n, m);
    rezultatai (M, n, m);
    return 0;
}
void skaitymas (duomenys M[], int n)
{
    for(int i=0; i<n; i++)
    {
        cout<< "Iveskite mokinio varda:";
        cin>> M[i].v;
        cout<< "Iveskite mokinio pavarde:";
        cin>> M[i].p;
        cout<< "Iveskite mokinio pazymiu kieki:";
        cin>>M[i].paz;
        cout<< "Iveskite mokinio pazymius:";
        for (int j=0; j<M[i].paz; j++)
        {
        cin>> M[i].N[j];
        }
        cout<< "Iveskite mokinio egzamino rezultata:";
        cin>>M[i].e;
    }
}
void skaiciavimas (duomenys M[], int n, int m)
{
    for(int i=0; i<n; i++)
    {
        if (m==1)
        {
        M[i].r=vid (M, i)*0.4+M[i].e*0.6;
        }
        else M[i].r=mediana (M, i)*0.4+M[i].e*0.6;
    }
}
double vid (duomenys M[], int i)
{
    double sum=0;
    for (int j=0; j<5; j++)
    {
        sum+=M[i].N[j];
    }
    return sum/5;
}
double mediana(duomenys M[], int i)
{

    sort(M[i].N, M[i].N + M[i].paz);
    if (M[i].paz % 2 != 0) 
    {
        return M[i].N[M[i].paz / 2];
    }
    else {
        return (M[i].N[(M[i].paz - 1) / 2] + M[i].N[M[i].paz / 2]) / 2.0;
    }
}
void rezultatai (duomenys M[], int n, int m)
{
    cout<<left<<setw (13)<<setfill(' ')<< "Pavardė"<<left<<setw (13)<<setfill(' ') << "Vardas";
    if (m==1)
    {
        cout<<"Galutinis (Vid.)"<<endl;
    }
    else cout<< "Galutinis (Med.)"<<endl;
    cout<<setw (60)<<setfill('-')<<"-"<<endl;
    for (int i=0; i<n; i++)
    {
        cout<<left<<setw (12)<<setfill(' ')<< M[i].p <<left<<setw (13)<<setfill(' ')<< M[i].v <<left<<setw (20)<<setfill(' ') <<fixed<<setprecision(2)<< M[i].r <<endl;
    }
}
