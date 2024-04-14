//TP 2022/2023: Zadaća 5, Zadatak 2
#include <functional>
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <iterator>

class Padavine{
    std::vector<int> kolicinaPadavina; //padavine u centimetrima
    int maxKolicinaPadavina;
   public:
    explicit Padavine(int maxKolicina=0);
    void RegistrirajPadavine(int kolicina);
    int DajBrojRegistriranihPadavina() const {return static_cast<int>(kolicinaPadavina.size());}
    void BrisiSve(){kolicinaPadavina.resize(0);}
    int DajMinimalnuKolicinuPadavina()const;
    int DajMaksimalnuKolicinuPadavina()const;
    int DajBrojDanaSaPadavinamaVecimOd(int parametar) const;
    void Ispisi()const;
    int operator[](int indeks) const;
    Padavine &operator ++();
    Padavine operator++(int);
    friend Padavine operator+(const Padavine &p1, const int &broj);
    friend Padavine operator+(const int &broj, const Padavine &p1);
    friend Padavine operator-(const Padavine &p1, const int &broj);
    friend Padavine operator-(const int &broj, const Padavine &p1);
    friend Padavine operator-(const Padavine &p1, const Padavine &p2);
    Padavine &operator-=(const Padavine &p);
    Padavine &operator+=(const int &broj);
    Padavine &operator-=(const int &broj);
    Padavine operator-();
    friend bool operator==(const Padavine &p1, const Padavine &p2);
    friend bool operator!=(const Padavine &p1, const Padavine &p2);
};

Padavine::Padavine(int maxKolicina){
    if(maxKolicina<=0) throw std::range_error("Ilegalna maksimalna kolicina");
    Padavine::maxKolicinaPadavina=maxKolicina;
}

void Padavine::RegistrirajPadavine(int kolicina){
    if(kolicina</*=*/0 || kolicina>maxKolicinaPadavina) throw std::range_error("Ilegalna kolicina padavina");
    Padavine::kolicinaPadavina.push_back(kolicina);
}

int Padavine::DajMinimalnuKolicinuPadavina() const{
    if(kolicinaPadavina.size()==0) throw std::range_error("Nema registriranih padavina");
    auto it=std::min_element(kolicinaPadavina.begin(), kolicinaPadavina.end());
    return *it;
}

int Padavine::DajMaksimalnuKolicinuPadavina() const{
    if(kolicinaPadavina.size()==0) throw std::range_error("Nema registriranih padavina");
    auto it=std::max_element(kolicinaPadavina.begin(), kolicinaPadavina.end());
    return *it;
}

int Padavine::DajBrojDanaSaPadavinamaVecimOd(int parametar) const{
    if(kolicinaPadavina.size()==0) throw std::range_error("Nema registriranih padavina");
    //int broj=std::count_if(kolicinaPadavina.begin(), kolicinaPadavina.end(), [&parametar](int n){return n>parametar;});
    int broj=std::count_if(kolicinaPadavina.begin(), kolicinaPadavina.end(),std::bind(std::greater<int>(), std::placeholders::_1, parametar));
    return broj;
}

void Padavine::Ispisi() const{
    std::vector<int> temp=kolicinaPadavina;
    //std::sort(temp.begin(), temp.end(), [](const int &broj1, const int &broj2){return broj1<broj2;})
    //std::sort(temp.begin(), temp.end(), std::greater<int>());
    std::sort(temp.rbegin(), temp.rend());
    //std::for_each(temp.begin(), temp.end(), [](const int &broj){std::cout<<broj<<std::endl;});
    std::copy(temp.begin(), temp.end(), std::ostream_iterator<int>(std::cout,"\n"));
}

int Padavine::operator[](int indeks) const{
    if(indeks<1 || indeks>=kolicinaPadavina.size()) throw std::range_error("Neispravan indeks");
    return kolicinaPadavina[indeks-1];
}

Padavine & Padavine::operator++(){
    maxKolicinaPadavina++;
    std::transform(kolicinaPadavina.begin(), kolicinaPadavina.end(), kolicinaPadavina.begin(), std::bind(std::plus<int>(), std::placeholders::_1, 1));
    return *this;
}

Padavine Padavine::operator++(int){
    Padavine temp=*this;
    ++(*this);
    return temp;
}

Padavine operator+(const Padavine &p1, const int &broj){
    Padavine novi(p1.DajBrojRegistriranihPadavina()+broj);
    novi.kolicinaPadavina.resize(p1.kolicinaPadavina.size());
    std::transform(p1.kolicinaPadavina.begin(), p1.kolicinaPadavina.end(), novi.kolicinaPadavina.begin(), std::bind(std::plus<int>(), std::placeholders::_1, broj));
    return novi;
}

Padavine operator+(const int &broj, const Padavine &p1){
    return p1+broj;
}

Padavine operator-(const Padavine &p1, const int &broj){
    Padavine novi(p1.DajBrojRegistriranihPadavina()-broj);
    novi.kolicinaPadavina.resize(p1.kolicinaPadavina.size());
    std::transform(p1.kolicinaPadavina.begin(), p1.kolicinaPadavina.end(), novi.kolicinaPadavina.begin(), std::bind(std::minus<int>(), std::placeholders::_1, broj));
    int broj_manjih_od_nula=std::count_if(novi.kolicinaPadavina.begin(), novi.kolicinaPadavina.end(),std::bind(std::less<int>(), std::placeholders::_1, 0));
    if(broj_manjih_od_nula>0){
        novi.kolicinaPadavina.resize(0);
        throw std::domain_error("Nekorektan rezultat operacije");
    }
    return novi;
}

Padavine operator-(const int &broj, const Padavine &p1){
    Padavine novi(broj);
    novi.kolicinaPadavina.resize(p1.kolicinaPadavina.size());
    std::transform(p1.kolicinaPadavina.begin(), p1.kolicinaPadavina.end(), novi.kolicinaPadavina.begin(), std::bind(std::minus<int>(), broj, std::placeholders::_1));
    int broj_manjih_od_nula=std::count_if(novi.kolicinaPadavina.begin(), novi.kolicinaPadavina.end(),std::bind(std::less<int>(), std::placeholders::_1, 0));
    if(broj_manjih_od_nula>0){
        novi.kolicinaPadavina.resize(0);
        throw std::domain_error("Nekorektan rezultat operacije");
    }
    return novi;
}

Padavine operator-(const Padavine &p1, const Padavine &p2){
    if(p1.kolicinaPadavina.size()!=p2.kolicinaPadavina.size()) throw std::domain_error("Nesaglasni operandi");
    Padavine p(p1.maxKolicinaPadavina);
    p.kolicinaPadavina.resize(p1.kolicinaPadavina.size());
    std::transform(p1.kolicinaPadavina.begin(), p1.kolicinaPadavina.end(), p2.kolicinaPadavina.begin(), p.kolicinaPadavina.begin(), std::minus<int>());
    int broj_manjih_od_nula=std::count_if(p.kolicinaPadavina.begin(), p.kolicinaPadavina.end(),std::bind(std::less<int>(), std::placeholders::_1, 0));
    if(broj_manjih_od_nula>0){
        p.kolicinaPadavina.resize(0);
        throw std::domain_error("Nekorektan rezultat operacije");
    }
    return p;
}

Padavine & Padavine::operator-=(const Padavine &p){
    *this=*this-p;
    return *this;
}

Padavine & Padavine::operator+=(const int &broj){
    *this=*this+broj;
    return *this;
}

Padavine & Padavine::operator-=(const int &broj){
    *this=*this-broj;
    return *this;
}

Padavine Padavine::operator-(){
    Padavine novi(this->maxKolicinaPadavina);
    novi.kolicinaPadavina.resize(this->kolicinaPadavina.size());
    std::transform(this->kolicinaPadavina.begin(), this->kolicinaPadavina.end(), novi.kolicinaPadavina.begin(), std::bind(std::minus<int>(), this->maxKolicinaPadavina, std::placeholders::_1));
    return novi;
}

bool operator==(const Padavine &p1, const Padavine &p2){
    if(p1.kolicinaPadavina.size()!=p2.kolicinaPadavina.size()) return false;
    return p1.kolicinaPadavina==p2.kolicinaPadavina;
}

bool operator!=(const Padavine &p1, const Padavine &p2){
    return !(p1==p2);
}

int main (){
    try{
        Padavine p(60);
        p.RegistrirajPadavine(10);
        p.RegistrirajPadavine(30);
        p.RegistrirajPadavine(40);
        std::cout<<"Broj registriranih padavina je "<<p.DajBrojRegistriranihPadavina()<<
            ", medju kojima je maksimalna kolicina "<<p.DajMaksimalnuKolicinuPadavina()<<", a minimalna "<<p.DajMinimalnuKolicinuPadavina()<<std::endl;
        std::cout<<"Broj dana sa padavinama vecim od 30 je "<<p.DajBrojDanaSaPadavinamaVecimOd(30)<<std::endl;
        std::cout<<"Pregled kolicine padavina: "; p.Ispisi();

        p++;
        std::cout<<"Pregled kolicine padavina sada izgleda ovako: "; p.Ispisi();
        p=-p;
        std::cout<<"Pregled kolicine padavina sada izgleda ovako: "; p.Ispisi();
        std::cout<<"Kolicona padavina prvi dan iznosi: "<<p[1]<<std::endl;
    }
    catch(std::domain_error &izuzetak){
        std::cout<<izuzetak.what()<<std::endl;
    }
	return 0;
}
