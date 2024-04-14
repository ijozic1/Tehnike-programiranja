//TP 2022/2023: LV 12, Zadatak 2
#include <iostream>
#include <set>
#include <utility>
#include <ostream>

template <typename Tip>
std::set<Tip> operator+(const std::set<Tip> &Skup1, const std::set<Tip> &Skup2){
    std::set<Tip>UnijaSkupova;
    for(Tip x : Skup1) UnijaSkupova.insert(x);
    for(Tip x : Skup2) UnijaSkupova.insert(x);
    return UnijaSkupova;
}

template <typename Tip>
std::set<Tip> operator *(const std::set<Tip> &Skup1, const std::set<Tip> &Skup2){
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

template <typename Tip>
void operator+=(std::set<Tip>& Skup1, const std::set<Tip>& Skup2) {
   Skup1=Skup1+Skup2;
}

template <typename Tip>
void operator*=(std::set<Tip>& Skup1, const std::set<Tip>& Skup2) {
   Skup1=Skup1*Skup2;
}

template <typename T1, typename T2>
std::ostream& operator<<(std::ostream& tok, const std::pair<T1, T2>& par) {
    tok << "(" << par.first << "," << par.second << ")";
    return tok;
}

template <typename T>
std::ostream& operator<<(std::ostream& tok, const std::set<T>& skup) {
    tok << "{";
    auto it = skup.begin();
    if (it != skup.end()) {
        tok << *it;
        ++it;
    }
    for (; it != skup.end(); ++it) {
        tok << ","<< *it;
    }
    tok << "}";
    return tok;
}

template <typename T1, typename T2>
std::set<std::pair<T1, T2>> operator%(const std::set<T1>& skup1, const std::set<T2>& skup2) {
    std::set<std::pair<T1, T2>> rezultat;
    for (const auto& element1 : skup1) {
        for (const auto& element2 : skup2) {
            rezultat.insert(std::make_pair(element1, element2));
        }
    }
    return rezultat;
}

int main() {
    std::set<int> s1{3, 5, 1, 2, 8}, s2{7, 2, 8, 4};
    std::cout << s1 + s2 << std::endl; 
    std::cout << s1 * s2 << std::endl; 

    std::set<char> s3{'A', 'B'};
    std::set<int> s4{1, 2, 3};
    std::cout << s3 % s4 << std::endl;

    return 0;
}
