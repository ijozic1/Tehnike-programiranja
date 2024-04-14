//TP 2022/2023: LV 2, Zadatak 4
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
        double re, im;
        std::cout<<"R"<<i+1<<" = ";
        std::cin>>re;
        std::cout<<"X"<<i+1<<" = ";
        std::cin>>im;
        std:: cout<<std::endl;
        z=Kompleksni(re,im);
        suma+=1./z;
    }
    suma=1./suma;

    std::cout<<"Paralelna veza ovih elemenata ima R = "<<suma.real()<<" i X = "<<suma.imag()<<"."<<std::endl;
	return 0;
}
