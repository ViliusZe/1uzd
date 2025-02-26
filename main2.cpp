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
int main()
{
    duomenys M[10];
    int n;
    cout<< "Iveskite mokiniu kieki:";
    cin>>n;
    cout<< endl;
    skaitymas(M, n);

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