//TP 2022/2023: LV 2, Zadatak 3
#include <iostream>
#include <cmath>
#include <complex>

typedef std::complex<double> Kompleksni;

int main (){
    Kompleksni z, suma(0,0);
    int broj;
    std:: cout<<"Unesite broj elemenata: ";
    std:: cin>> broj;
    std::cout<<std::endl;
    
    for(int i=0; i<broj; i++){
        std::cout<<"Z_"<<i+1<<" = ";
        std::cin>>z;
        suma+=1./z;
    }
    suma=1./suma;

    std::cout<<std::endl<<"Paralelna veza ovih elemenata ima impedansu Z_ = "<<suma<<"."<<std::endl;
	return 0;
}