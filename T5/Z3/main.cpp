// TP 2022/2023: LV 5, Zadatak 3
#include <algorithm>
#include <cmath>
#include <iostream>

void UnesiElement(int &clan) { std::cin >> clan; }

bool PotpunKvadrat(int clan) {
    return(floor(sqrt(clan))==ceil(sqrt(clan)));
}

bool NajmanjiBrojCifara(int a, int b){
    int brojCifara1=static_cast<int>(log10(abs(a))+1);
    int brojCifara2=static_cast<int>(log10(abs(b))+1);
    return brojCifara1<brojCifara2;
}

bool Netrocifren(int broj) {
    int brojCifara=static_cast<int>(log10(abs(broj))+1);
    return (brojCifara==3);
}

void Ispisi(int m){
    std::cout<<m<<" ";
}

int main() {
    std::cout << "Unesite broj elemenata (max. 1000): ";
    int velicina = 0;
    std::cin >> velicina;
    std::cout << "Unesite elemente: ";
    int niz[1000];
    std::for_each(niz, niz + velicina, UnesiElement);
    std::cout << "Najveci element niza je "<< *std::max_element(niz, niz + velicina)<<" "<<std::endl;
    std::cout << "Najmanji element niza se pojavljuje "<< std::count(niz, niz + velicina,*std::min_element(niz, niz + velicina))<< " puta u nizu" << std::endl;
    std::cout << "U nizu ima "<< std::count_if(niz, niz + velicina, PotpunKvadrat)<< " brojeva koji su potpuni kvadrati" << std::endl;
    std::cout<<"Prvi element sa najmanjim brojem cifara je "<<*std::min_element(niz, niz+velicina, NajmanjiBrojCifara)<<std::endl;
    auto kraj=std::remove_if(niz, niz+velicina, Netrocifren);
    std::cout << "Elementi koji nisu trocifreni su: ";
    std::for_each(niz, kraj, Ispisi);
    std::cout<<std::endl; 
    return 0;
}