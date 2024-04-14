//TP 2022/2023: LV 11, Zadatak 1
#include <iostream>
#include <cmath>

class NeobicnaKlasa {
    int broj;
public:
    explicit NeobicnaKlasa(int x) : broj(x) {
        std::cout << "Direktna inicijalizacija" << std::endl;
    }
    NeobicnaKlasa(double x) : broj(x) {
        std::cout << "Kopirajuca inicijalizacija" << std::endl;
    }
    NeobicnaKlasa(const NeobicnaKlasa &objekat) : broj(objekat.broj){
        std::cout<<"Kopirajuci konstruktor"<<std::endl;
    }
    void Ispisi() const{
        std::cout<<broj<<std::endl;
    }
};

int main() {
    NeobicnaKlasa k1(10);          // Proizvodi ispis "Direktna inicijalizacija"
    NeobicnaKlasa k2 = 5;         // Proizvodi ispis "Kopirajuća inicijalizacija"
    NeobicnaKlasa k3=k2;         //Ovdje poziva kopirajuci konstruktor
    k3=k1;
    k3.Ispisi();
    return 0;
}