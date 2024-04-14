// TP 2022/2023: Zadaća 1, Zadatak 1
#include <array>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <vector>

enum class TretmanNegativnih { IgnorirajZnak, Odbaci, PrijaviGresku };

std::vector<long long int> UnesiElemente() {
    std::vector<long long int> brojevi;
    long long int broj=0;
    while (std::cin >> broj)
        brojevi.push_back(broj);
    return brojevi;
}

long long int ProizvodCifara(long long int broj, const int &baza) {
    if (broj == 0)
        return 1;
    return (broj % baza) * ProizvodCifara(broj / baza, baza);
}

long long int MultiplikativniDigitalniKorijen(long long int broj, const int &baza) {
    if (baza < 2)
        throw std::domain_error("Neispravna baza");
    if(broj<baza) return broj;
    broj = ProizvodCifara(broj, baza);
    return MultiplikativniDigitalniKorijen(broj, baza);
}

std::array<std::vector<long long int>, 10> RazvrstajBrojeve(const std::vector<long long int> &brojevi, TretmanNegativnih tretman) {
    std::array<std::vector<long long int>, 10> razvrstano;
    for (int i = 0; i < brojevi.size(); i++) {
        if (brojevi.at(i) < 0) {
            if (tretman == TretmanNegativnih::IgnorirajZnak) {
                int broj=brojevi[i] * (-1);
                razvrstano.at(MultiplikativniDigitalniKorijen(broj, 10)).push_back(broj);
            } 
            else if (tretman == TretmanNegativnih::PrijaviGresku)
                throw std::domain_error("Nije predvidjeno razvrstavanje negativnih brojeva");
        } 
        else
            razvrstano.at(MultiplikativniDigitalniKorijen(brojevi.at(i), 10)).push_back(brojevi.at(i));
    }
  return razvrstano;
}

int main() {
    std::cout << "Unesite brojeve (bilo koji ne-broj oznacava kraj): ";
    std::vector<long long int> VektorBrojeva= UnesiElemente();
    std::cout << std::endl;
    TretmanNegativnih tretman = TretmanNegativnih::PrijaviGresku;
    try {
        auto razvrstano = RazvrstajBrojeve(VektorBrojeva, tretman);
        std::cout<< "Rezultati razvrstavanja po multiplikativnom digitalnom korijenu:"<< std::endl;
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < razvrstano.at(i).size(); j++) {
                if (j == 0) std::cout << i << ": ";
                std::cout << razvrstano.at(i).at(j) << " ";
            }
            std::cout << std::endl;
        }   
    } 
    catch (/*const*/std::domain_error &izuzetak) {
        std::cout << "Nije podrzano razvrstavanje negativnih brojeva!";
    }
    return 0;
}