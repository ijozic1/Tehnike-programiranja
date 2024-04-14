// TP 2022/2023: LV 4, Zadatak 4
#include <cctype>
#include <cmath>
#include <iostream>
#include <string>

template <typename NekiTip>
void UnosBroja(const std::string &unos, const std::string &upozorenje, NekiTip &broj) {
    bool UspjesanUnos = true;
    NekiTip sadrzaj;
    while(1) {
        std::cout << unos;
        std::cin>>sadrzaj;
        if(!std::cin.fail() && std::cin.peek()=='\n') break;
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << upozorenje << std::endl;
    }
    broj = sadrzaj;
}

double Stepenuj(double baza, int eksponent) {
    if (eksponent==0) return 1;
    return eksponent>0 ? (baza * Stepenuj(baza, eksponent - 1)) : (1. / baza * Stepenuj(baza, eksponent + 1));
}

int main() {
    double baza;
    UnosBroja("Unesite bazu: ", "\nNeispravan unos, pokusajte ponovo...", baza);
    int eksponent;
    UnosBroja("Unesite cjelobrojni eksponent: ", "\nNeispravan unos, pokusajte ponovo...", eksponent);
    std::cout<<baza<<" na "<<eksponent<<" iznosi "<<Stepenuj(baza, eksponent);
    /*int broj;
    UnosBroja("Unesi broj: ", "Pogresan unos!", broj);
    std::cout << std::endl << broj;*/
    return 0;
}