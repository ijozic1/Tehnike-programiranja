// TP 2022/2023: LV 4, Zadatak 3
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

bool DaLiJeVeci(std::string prvi, std::string drugi) {
    int velicina;
    if (prvi.size() < drugi.size())  velicina = prvi.size();
    else  velicina = drugi.size();
    for (int i = 0; i < velicina; i++) {
        if(i==velicina-1 && tolower(prvi.at(i)) == tolower(drugi.at(i)) && prvi.size()>drugi.size()) return true;
        if (tolower(prvi.at(i)) > tolower(drugi.at(i))) return true;
        if (tolower(prvi.at(i)) < tolower(drugi.at(i))) return false;
    }
    return false;
}

bool DaLiJeManji(std::string prvi, std::string drugi) {
    int velicina;
    if (prvi.size() < drugi.size()) velicina = prvi.size();
    else velicina = drugi.size();
    for (int i = 0; i < velicina; i++) {
        if(i==velicina-1 && tolower(prvi.at(i)) == tolower(drugi.at(i)) && prvi.size()<drugi.size()) return true;
        if (tolower(prvi.at(i)) > tolower(drugi.at(i))) return false;
        if (tolower(prvi.at(i)) < tolower(drugi.at(i))) return true;
    }
    return false;
}

void IzdvojiKrajnjeRijeci(const std::vector<std::string> &Spisak, std::string &PrvaRijec, std::string &PosljednjaRijec) {
    PrvaRijec = "";
    PosljednjaRijec = "";
    if (Spisak.size() > 0) {
        PrvaRijec = Spisak.at(0);
        PosljednjaRijec = Spisak.at(0);
    }
    for (int i = 0; i < Spisak.size(); i++) {
        if (DaLiJeVeci(Spisak.at(i), PosljednjaRijec)) PosljednjaRijec = Spisak.at(i);
        if (DaLiJeManji(Spisak.at(i), PrvaRijec)) PrvaRijec = Spisak.at(i);
    }
}

void Prepisi(std::vector<std::string> &spisak, int &j) {
    for (int k = j; k < spisak.size() - 1; k++)
        spisak.at(k) = spisak.at(k + 1);
    spisak.resize(spisak.size() - 1);
    j--;
}

void ZadrziDuplikate(std::vector<std::string> &spisak) {
    bool Duplikat = false;
    for (int i = 0; i < spisak.size(); i++) {
        Duplikat = false;
        for (int j = i + 1; j < spisak.size(); j++) {
            if (spisak.at(i) == spisak.at(j)) {
                Duplikat = true;
                Prepisi(spisak, j);
            }
        }
        if (!Duplikat) Prepisi(spisak, i);
    }
}

int main() {
    std::cout << "Koliko zelite unijeti rijeci: ";
    int n;
    std::cin >> n;
    std::vector<std::string> rijeci(n);
    std::cout << "Unesite rijeci: ";
    for (int i = 0; i < n; i++)
        std::cin>>rijeci.at(i);
    std::string PrvaRijec, PosljednjaRijec;
    IzdvojiKrajnjeRijeci(rijeci, PrvaRijec, PosljednjaRijec);
    std::cout << "Prva rijec po abecednom poretku je: " << PrvaRijec << std::endl;
    std::cout << "Posljednja rijec po abecednom poretku je: " << PosljednjaRijec<< std::endl;
    ZadrziDuplikate(rijeci);
    std::cout << "Rijeci koje se ponavljaju su: ";
    for (std::string s : rijeci)
        std::cout << s << " ";
    std::cout << std::endl;
    return 0;
}