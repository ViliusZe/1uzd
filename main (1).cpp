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
void skaiciavimas (duomenys M[], int n);
double vid (duomenys M[], int i);
void rezultatai (duomenys M[], int n);
int main()
{
    duomenys M[10];
    int n;
    cout<< "Iveskite mokiniu kieki:";
    cin>>n;
    cout<< endl;
    skaitymas(M, n);
    skaiciavimas (M, n);
    rezultatai (M, n);
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
void skaiciavimas (duomenys M[], int n)
{
    for(int i=0; i<n; i++)
    {
        M[i].r=vid (M, i)*0.4+M[i].e*0.6;
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
void rezultatai (duomenys M[], int n)
{
    cout<<left<<setw (13)<<setfill(' ')<< "Pavardė"<<left<<setw (13)<<setfill(' ') << "Vardas"<<"Galutinis (Vid.)";
    cout<<setw (60)<<setfill('-')<<"-"<<endl;
    for (int i=0; i<n; i++)
    {
        cout<<left<<setw (12)<<setfill(' ')<< M[i].p <<left<<setw (13)<<setfill(' ')<< M[i].v <<left<<setw (20)<<setfill(' ') <<fixed<<setprecision(2)<< M[i].r <<endl;
    }
}