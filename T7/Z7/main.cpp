//TP 2022/2023: LV 7, Zadatak 7
#include <iostream>
#include <cmath>
#include <set>

template <typename Tip>
std::set<Tip> Unija(const std::set<Tip> &Skup1, const std::set<Tip> &Skup2){
    std::set<Tip>UnijaSkupova;
    for(Tip x : Skup1) UnijaSkupova.insert(x);
    for(Tip x : Skup2) UnijaSkupova.insert(x);
    return UnijaSkupova;
}

template <typename Tip>
std::set<Tip> Presjek(const std::set<Tip> &Skup1, const std::set<Tip> &Skup2){
    std::set<Tip>PresjekSkupova;
    for(Tip x : Skup1){
        for(Tip y : Skup2)
            if(x==y){
                PresjekSkupova.insert(x);
                break;
            }
    }
    return PresjekSkupova;
}

int main (){
    std::set<std::string> s1{"A", "B", "C", "C", "C"}, s2{"B", "B", "D"};
    std::cout<<"Unija: ";
    for(auto x: Unija(s1, s2)) std::cout << x << " ";
    std::cout << std::endl<<"Presjek: ";
    for(auto x: Presjek(s1, s2)) std::cout << x << " ";
    std::cout << std::endl;
	return 0;
}