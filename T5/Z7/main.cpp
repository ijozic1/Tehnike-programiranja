//TP 2022/2023: LV 5, Zadatak 7
#include <iostream>
#include <cmath>
#include <deque>
#include <stdexcept>

template<typename Iterator>
auto SumaBloka(Iterator pocetak, Iterator IzaKraja) -> decltype(*pocetak + *pocetak){
    if (pocetak == IzaKraja) throw std::range_error("Blok je prazan");
    decltype(*pocetak + *pocetak) suma = *pocetak;
    pocetak++;
    while(pocetak!=IzaKraja) suma+=*pocetak++;
    return suma;
}

int main(){
    std::deque<double> kolekcija;
    double x;
    while (std::cin >> x) kolekcija.push_back(x);
    try {
        std::cout << "Suma bloka: " << SumaBloka(kolekcija.begin(), kolekcija.end()) << std::endl;
    } 
    catch (const std::range_error &izuzetak) {
        std::cerr << "Greška: " << izuzetak.what() << std::endl;
    }
    return 0;
}