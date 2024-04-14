// TP 2022/2023: Zadaća 1, Zadatak 4
#include <cctype>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

bool UporediRijeci(const std::string &dioRecenice, const std::string &rijec) {
    if (dioRecenice == rijec) return true;
    if (dioRecenice.length() != rijec.length()) return false;
    for (int i = 0; i < rijec.length(); i++)
        if (toupper(dioRecenice.at(i)) != toupper(rijec.at(i))) return false;
    return true;
}

bool IspravnaRijec(const std::string &rijec) {
    for (int i = 0; i < rijec.length(); i++)
        if (!isalpha(rijec.at(i)) && !isdigit(rijec.at(i))) return false;
    return true;
}

std::string Cenzura(std::string recenica, const std::vector<std::string> &SpisakRijeci) {
    for (int i = 0; i < SpisakRijeci.size(); i++)
        if (!IspravnaRijec(SpisakRijeci.at(i))) throw std::logic_error("Neispravna riječ");
    for (int i = 0; i < recenica.length(); i++) {
        if (isalpha(recenica.at(i)) || isdigit(recenica.at(i))) {
            int PocetakRijeci = i;
            std::string RijecURecenici;
            while (i < recenica.length() && (isalpha(recenica.at(i)) || isdigit(recenica.at(i)))) {
                RijecURecenici.push_back(recenica.at(i));
                i++;
            } 
            int KrajRijeci = i;
            bool podudaranje = false;
            for (int j = 0; j < SpisakRijeci.size(); j++) {
                if(UporediRijeci(RijecURecenici, SpisakRijeci.at(j))){
                    podudaranje =true;
                    break;
                }
            }
            if (podudaranje) {
                while (PocetakRijeci < KrajRijeci) {
                    recenica.at(PocetakRijeci) = '*';
                    PocetakRijeci++;
                }
            }
        }
    }
    return recenica;
}
int main() {
    std::cout << "Unesite recenicu: ";
    std::string recenica;
    getline(std::cin, recenica);
    std::cout << "Unesite zabranjene rijeci (. za kraj): ";
    std::vector<std::string> SpisakRijeci;
    std::string rijec;
    do {
        std::cin >> std::ws;
        std::cin >> rijec;
        if (rijec != ".") SpisakRijeci.push_back(rijec);
    } while (rijec != ".");
    try {
        recenica=Cenzura(recenica, SpisakRijeci);
        std::cout << std::endl << "Cenzurisana recenica: " << recenica;
    } 
    catch (std::logic_error &izuzetak) {
        std::cout << "GRESKA: Nelegalne zabranjene rijeci!";
    }
    return 0;
}